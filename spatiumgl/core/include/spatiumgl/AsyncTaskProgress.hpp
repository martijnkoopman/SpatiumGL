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

#ifndef SPATIUMGL_ASYNCTASKPROGRESS_H
#define SPATIUMGL_ASYNCTASKPROGRESS_H

#include "spatiumglexport.hpp"

#include <atomic> // std::atomic
#include <mutex>  // std::mutex
#include <string> // std::string

namespace spgl {

/// \class AsyncTaskProgress
/// \brief Progress of a AsyncTask
class SPATIUMGL_EXPORT AsyncTaskProgress
{
  template<typename T>
  friend class AsyncTask;

public:
  /// Constructor.
  AsyncTaskProgress()
    : m_percentage()
    , m_message("")
    , m_messageMutex()
  {
    m_percentage.store(0);
  }

  /// Get percentage.
  ///
  /// Range: 0 - 100
  ///
  /// \return Percentage
  int percentage() const { return m_percentage.load(); }

  /// Get progress message.
  ///
  /// \return Progress message
  std::string message()
  {
    std::lock_guard<std::mutex> guard(m_messageMutex);
    return m_message; // copy?
  }

protected:
  /// Reset percentage and message.
  void reset()
  {
    setPercentage(0);
    setMessage("");
  }

  /// Set percentage.
  ///
  /// \param[in] percentage Percentage
  void setPercentage(int percentage) { m_percentage.store(percentage); }

  /// Set message.
  ///
  /// \param[in] message Message
  void setMessage(const std::string& message)
  {
    std::lock_guard<std::mutex> guard(m_messageMutex);
    m_message = message; // copy?
  }

private:
  std::atomic<int> m_percentage;
  // std::string is not a trivially copyable type and therefor std::atomic is
  // not an option -> use std::mutex.
  std::string m_message;
  std::mutex m_messageMutex;
};

} // namespace spgl

#endif // SPATIUMGL_ASYNCTASKPROGRESS_H
