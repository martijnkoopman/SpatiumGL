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
#include "AsyncTaskProgress.hpp"

#include <thread> // std::thread
#include <atomic> // std::atomic
#include <mutex>  // std::mutex
#include <string> // std::string

namespace spgl {

/// \class RunningGaurd
/// \brief Gaurd for running flag.
///
/// RunningGaurd ensures a boolean lvalue, passed as reference in the
/// constructor, is set to true during the lifetime of the instance. When the
/// RunningGaurd goes out of scope the boolean lvalue is set to false.
class SPATIUMGL_EXPORT RunningGaurd
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
    , m_progress()
  {
    m_running.store(false);
    m_cancel.store(false);
  }

  /// Copy constructor.
  AsyncTask(const AsyncTask& other) = delete;

  /// Move constructor.
  AsyncTask(AsyncTask&& other) = default;

  /// Copy assignment operator.
  AsyncTask& operator=(const AsyncTask& other) = delete;

  /// Move assignment operator.
  AsyncTask& operator=(AsyncTask&& other) = default;

  /// Destructor
  virtual ~AsyncTask() = default; // required for pure virtual run()

  /// Start task (if not running).
  ///
  /// \return True if started, false otherwise
  bool start()
  {
    if (m_thread == nullptr) {

      // Re-set progress
      m_progress.reset();

      // Clear result
      setResult(nullptr);

      // Create thread
      m_thread = std::unique_ptr<std::thread>(
        new std::thread(&AsyncTask::run, this));

      m_running = true;

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

  /// Get progress.
  ///
  /// \return Progress
  AsyncTaskProgress& progress() { return m_progress; }

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

  /// Set progress message.
  ///
  /// \param[in] message Progress message
  void setProgressMessage(const std::string& message)
  {
    m_progress.setMessage(message);
  }

  /// Set progress percentage.
  ///
  /// \param[in] message Progress percentage
  void setProgressPercentage(int percentage)
  {
    m_progress.setPercentage(percentage);
  }

private:
  std::unique_ptr<std::thread> m_thread;
  std::atomic<bool> m_running;
  std::atomic<bool> m_cancel;
  // std::shared_ptr<> is not a trivially copyable type and therefor
  // std::atomic is not an option -> use std::mutex.
  std::shared_ptr<T> m_result;
  std::mutex m_resultMutex;
  AsyncTaskProgress m_progress;
};

} // namespace spgl

#endif // SPATIUMGL_ASYNCTASK_H
