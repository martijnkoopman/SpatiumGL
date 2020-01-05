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

#ifndef SPATIUMGL_MATH_H
#define SPATIUMGL_MATH_H

#include "spatiumglexport.hpp"

#include <type_traits> // std::enable_if
#include <limits>      // std::numeric_limits
#include <cmath>       // std::fabs

namespace spgl {

/// Pi constant
template<typename T>
constexpr T
PI()
{
  return 3.141592653589793238462643383279502884e+00;
}

/// Radians to degrees conversion constant (180 / PI)
template<typename T>
constexpr T
Rad2Deg()
{
  return 5.729577951308232087679815481410517033e+01;
}

/// Degrees to radians conversion constant (PI / 180)
template<typename T>
constexpr T
Deg2Rad()
{
  return 1.745329251994329576923690768488612713e-02;
}

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almostEqual(T x, T y, int ulp)
{
  return std::fabs(x - y) <=
           std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp ||
         std::fabs(x - y) < std::numeric_limits<T>::min();
}

} // namespace spgl

#endif // SPATIUMGL_MATH_H
