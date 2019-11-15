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

namespace spatiumgl {

	/// Pi constant
	template<typename T>
	constexpr T PI()
	{
		return 3.141592653589793238462643383279502884e+00;
	}

	/// Radians to degrees conversion constant (180 / PI)
	template<typename T>
	constexpr T Rad2Deg()
	{
		return 5.729577951308232087679815481410517033e+01;
	}

	/// Degrees to radians conversion constant (PI / 180)
	template<typename T>
	constexpr T Deg2Rad()
	{
		return 1.745329251994329576923690768488612713e-02;
	}

} // namespace spatiumgl

#endif // SPATIUMGL_MATH_H
