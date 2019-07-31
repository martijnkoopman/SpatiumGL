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

#ifndef SPATIUMGL_MATRIX_H
#define SPATIUMGL_MATRIX_H

#include "Vector.hpp"

namespace spatiumgl {

template<typename T, size_t W, size_t H>
class Matrix
{
	// Override operators:
	// +
	// -
	// *
	// With other matrix, with vector and with scalars

protected:
	std::array<std::array<T, W>, H> m_data;
};

template<typename T>
class Matrix3<T> : public Matrix<T, 3, 3>
{
	// Rotation

};

template<typename T>
class Matrix4<T> : public Matrix<T, 4, 4>
{
	// Translation

	// Projection

};

} // namespace spatiumgl

#endif // SPATIUMGL_MATRIX_H