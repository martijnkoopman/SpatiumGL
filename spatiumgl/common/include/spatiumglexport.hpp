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

#ifdef __linux__
#  if defined(SPATIUMGL_LIBRARY)
#    define SPATIUMGL_EXPORT __attribute__((visibility("default")))
#  else
#    define SPATIUMGL_EXPORT
#  endif
#endif
#ifdef _WIN32
#  if defined(SPATIUMGL_LIBRARY)
#    define SPATIUMGL_EXPORT __declspec(dllexport)
#  else
#    define SPATIUMGL_EXPORT __declspec(dllimport)
#  endif
#endif
