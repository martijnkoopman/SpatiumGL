/*
 * Program: Spatium Graphics Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMGL_ASYNCTASK_H
#define SPATIUMGL_ASYNCTASK_H

#include "spatiumglexport.hpp"

#include <thread> // std::thread
#include <atomic> // std::atomic
#include <mutex>  // std::mutex
#include <string> // std::string

namespace spatiumgl {

/// \class RunningGaurd
/// \brief Gaurd for running flag.
///
/// RunningGaurd ensures a boolean lvalue, passed as reference in the
/// constructor, is set to true during the lifetime of the instance. When the
/// RunningGaurd goes out of scope the boolean lvalue is set to false.
class RunningGaurd SPATIUMGL_EXPORT
{
public:
  /// Constructor.
  ///
  /// \param[in] running Flag to set true while in scope
  RunningGaurd(std::atomic<bool>& running)
    : m_running(running)
  {
    m_running.store(true);
  }

  /// Copy constructor.
  RunningGaurd(const RunningGaurd& other) = delete;

  /// Move constructor.
  RunningGaurd(RunningGaurd&& other) = delete;

  /// Copy assignment operator.
  RunningGaurd& operator=(const RunningGaurd& other) = delete;

  /// Move assignment operator.
  RunningGaurd& operator=(RunningGaurd&& other) = delete;

  /// Destructor
  ~RunningGaurd() { m_running.store(false); }

private:
  std::atomic<bool>& m_running;
};

/// \class AsyncTask
/// \brief Asynchronous executed task (threaded)
template<typename T>
class SPATIUMGL_EXPORT AsyncTask {
public:

  /// Constructor
  AsyncTask()
    : m_thread(nullptr)
    , m_running()
    , m_cancel()
    , m_result(nullptr)
    , m_resultMutex()
    , m_progressPercentage()
    , m_progressMessage("")
    , m_progressMessageMutex()
  {
    m_running.store(false);
    m_cancel.store(false);
    m_progressPercentage.store(0);
  }

  /// Destructor
  virtual ~AsyncTask() = default; // required for pure virtual run()

  /// Start task (if not running).
  ///
  /// \return True if started, false otherwise
  bool start()
  {
    if (m_thread == nullptr) {

      // Re-set progress
      setProgressPercentage(0);
      setProgressMessage("");

      // Clear result
      setResult(nullptr);

      // Create thread
      m_thread = std::unique_ptr<std::thread>(
        new std::thread(&AsyncTask::run, this));

      return true;
    } else {
      return false;
    }
  }

  /// Wait for task to complete and join with current thread.
  ///
  /// This function should ALWAYS be called from the thread that initiated
  /// start(). This is a blocking function if the task hasn't completed yet.
  void join()
  {
    if (m_thread != nullptr) {
      m_thread->join();
    }
  }

  /// Check if task is running.
  ///
  /// \return True if running, false otherwise
  bool isRunning() const
  {
    if (m_thread != nullptr &&
        m_running.load() == true) {
      return true;
    } else {
      return false;
    }
  }

  /// Request task to be cancelled.
  ///
  /// This request should be fulfilled by the implementation of run(), but
  /// there is no guarantee for the caller.
  void cancel() { m_cancel.store(true); }

  /// Get progress percentage.
  ///
  /// Range: 0 - 100
  ///
  /// \return Progress
  int progressPercentage() { return m_progressPercentage.load(); }

  /// Get progress message.
  ///
  /// \return Progress message
  std::string progressMessage()
  {
    std::lock_guard<std::mutex> guard(m_progressMessageMutex);
    return m_progressMessage; // copy?
  }

  /// Get result of the task execution.
  ///
  /// Nullptr if task is still running or an error occured.
  ///
  /// \return Task result
  std::shared_ptr<T> result()
  {
    if (isRunning()) {
      return nullptr;
    } else {
      std::lock_guard<std::mutex> guard(m_resultMutex);
      return m_result;
    }
  }

protected:
  std::atomic<bool>& running() { return m_running; }

  bool shouldCancel() const { return m_cancel.load(); }

  /// Set progress percentage.
  ///
  /// \param[in] progress Progress
  void setProgressPercentage(int progress) { m_progressPercentage.store(progress); }

  /// Set progress message.
  ///
  /// \param[in] message Progress message
  void setProgressMessage(const std::string& message)
  {
    std::lock_guard<std::mutex> guard(m_progressMessageMutex);
    m_progressMessage = message; // copy?
  }

  /// Set task result.
  ///
  /// \param[in] result Task result
  void setResult(std::shared_ptr<T> result)
  {
    std::lock_guard<std::mutex> guard(m_resultMutex);
    m_result = result;
  }

  /// Perform task execution.
  ///
  /// This function is executed in another thread.
  /// This function must be implemented in subclasses of AsyncTask.
  /// The implementation MUST:
  /// - Set m_running to true at begin of execution.
  /// - Set m_running to false at end of execution.
  /// - Update m_progressPercentage during execution (Max 100 times, 1 time for
  ///   each percentage). (optional)
  /// - Read m_cancel occasionally to cancel execution.
  /// - Store result in m_result at end of execution. (nullptr on error)
  virtual void run() = 0;

private:
  std::unique_ptr<std::thread> m_thread;
  std::atomic<bool> m_running;
  std::atomic<bool> m_cancel;
  // std::shared_ptr<> is not a trivially copyable type and therefor
  // std::atomic is not an option -> use std::mutex.
  std::shared_ptr<T> m_result;
  std::mutex m_resultMutex;
  std::atomic<int> m_progressPercentage;
  // std::string is not a trivially copyable type and therefor std::atomic is
  // not an option -> use std::mutex.
  std::string m_progressMessage;
  std::mutex m_progressMessageMutex;
};

} // namespace spatiumgl

#endif // SPATIUMGL_ASYNCTASK_H
