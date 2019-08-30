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

#ifndef SPATIUMGL_MATRIX2X2_H
#define SPATIUMGL_MATRIX2X2_H

#include "Matrix.hpp"

namespace spatiumgl
{
	template<class T>
	struct SPATIUMGL_EXPORT Matrix<T, 2, 2> : public MatrixBase<T, 2, 2>
	{
		/// Default constructor
		///
		/// Sets all elements to 0.
		constexpr Matrix() = default;

		/// Constructor
		///
		/// Sets all elements to 0 except diagonal elements.
		///
		/// \param[in] diagional Diagonal value
		constexpr Matrix(T diagional)
			: MatrixBase()
		{
			m_data[0][0] = diagional;
			m_data[1][1] = diagional;
		}

		/// Constructor
		///
		/// \param[in] Data Initializer list with column-major ordering.
		constexpr Matrix(std::initializer_list<std::initializer_list<T>> data)
			: MatrixBase(data)
		{
		}

		// Compare operators

		/// Compare operator. Is equal.
		///
		/// \param[in] other Other matrix
		/// \return True if equal, otherwise false
		bool operator==(const Matrix<T, 3, 3> & other) const
		{
			if (m_data[0] != other.m_data[0]
				|| m_data[1] != other.m_data[1]
				|| m_data[2] != other.m_data[2])
			{
				return false;
			}
			return true;
		}

		/// Compare operator. Is unequal.
		///
		/// \param[in] other Other matrix
		/// \return True if unequal, otherwise false
		bool operator!=(const Matrix<T, 3, 3> & other) const
		{
			return !(operator ==(other));
		}

		// Arithmetic operators

		/// Add another matrix.
		///
		/// \param[in] other Matrix to add
		/// \return Added matrix
		constexpr Matrix<T, 3, 3> operator+(const Matrix<T, 2, 2> & other) const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = m_data[0][0] + other[0][0];
			result[0][1] = m_data[0][1] + other[0][1];
			result[1][0] = m_data[1][0] + other[1][0];
			result[1][1] = m_data[1][1] + other[1][1];
			return result;
		}

		/// Subtract other matrix.
		///
		/// \param[in] other Matrix to subtract
		/// \return Subtracted matrix
		constexpr Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2> & other) const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = m_data[0][0] - other[0][0];
			result[0][1] = m_data[0][1] - other[0][1];
			result[1][0] = m_data[1][0] - other[1][0];
			result[1][1] = m_data[1][1] - other[1][1];
			return result;
		}

		/// Multiply by scalar.
		///
		/// \param[in] scalar Scalar
		/// \return Multiplied vector
		constexpr Matrix<T, 2, 2> operator*(T scalar) const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = m_data[0][0] * scalar;
			result[0][1] = m_data[0][1] * scalar;
			result[1][0] = m_data[1][0] * scalar;
			result[1][1] = m_data[1][1] * scalar;
			return result;
		}

		/// Multiply by vector.
		///
		/// \param[in] vector Vector to multiply with
		/// \return Multiplied vector
		constexpr Vector<T, 2> operator*(const Vector<T, 2> & vector) const
		{
			Vector<T, 2> result;
			result[0] = m_data[0][0] * vector[0] + m_data[1][0] * vector[1];
			result[1] = m_data[0][1] * vector[0] + m_data[1][1] * vector[1];
			return result;
		}

		/// Divide by scalar.
		///
		/// \param[in] scalar Scalar
		/// \return Divided matrix
		constexpr Matrix<T, 2, 2> operator/(T scalar) const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = m_data[0][0] / scalar;
			result[0][1] = m_data[0][1] / scalar;
			result[1][0] = m_data[1][0] / scalar;
			result[1][1] = m_data[1][1] / scalar;
			return result;
		}

		// Matrix operations

		/// Get transposed matrix.
		///
		/// \return Transposed matrix
		constexpr Matrix<T, 2, 2> transposed() const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = m_data[0][0];
			result[0][1] = m_data[1][0];
			result[1][0] = m_data[0][1];
			result[1][1] = m_data[1][1];
			return result;
		}

		/// Calculate determinant.
		///
		/// \return Determinant
		constexpr T determinant() const
		{
			return m_data[0][0] * m_data[1][1] - m_data[1][0] * m_data[0][1];
		}

		/// Calculate inverse of matrix.
		///
		/// \throw std::out_of_range Matrix has no inverse
		/// \return Inverse of matrix
		constexpr Matrix<T, 2, 2> inverse() const
		{
			const T det = determinant();
			if (det == 0)
			{
				throw std::out_of_range("Matrix has no inverse (matrix is singular)");
			}

			Matrix<T, 2, 2> result;
			result[0][0] = m_data[1][1] / det;
			result[0][1] = -m_data[0][1] / det;
			result[1][0] = -m_data[1][0] / det;
			result[1][1] = m_data[0][0] / det;
			return result;
		}
	};
}

#endif // SPATIUMGL_MATRIX2X2_H