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
	template<typename T>
	struct SPATIUMGL_EXPORT Matrix<T, 2, 2> : public MatrixBase<T, 2, 2>
	{
		/// Default constructor
		///
		/// Sets all elements to 0.
		Matrix() = default;

		/// Constructor
		///
		/// Sets all elements to 0 except diagonal elements.
		///
		/// \param[in] diagional Diagonal value
		Matrix(T diagional)
			: MatrixBase<T, 2, 2>()
		{
			this->m_data[0][0] = diagional;
			this->m_data[1][1] = diagional;
		}

		/// Constructor
		///
		/// \param[in] Data Initializer list with column-major ordering.
		constexpr Matrix(std::initializer_list<std::initializer_list<T>> data)
			: MatrixBase<T, 2, 2>(data)
		{
		}

		/// Cast to matrix with different element type (static_cast).
		///
		/// \return Matrix with cast element type
		template<typename T2>
		Matrix<T2, 2, 2> staticCast() const
		{
			Matrix<T2, 2, 2> result;

			// Column 0
			result[0][0] = static_cast<T2>(this->m_data[0][0]);
			result[0][1] = static_cast<T2>(this->m_data[0][1]);

			// Column 1
			result[1][0] = static_cast<T2>(this->m_data[1][0]);
			result[1][1] = static_cast<T2>(this->m_data[1][1]);

			// Column 2
			result[2][0] = static_cast<T2>(this->m_data[2][0]);
			result[2][1] = static_cast<T2>(this->m_data[2][1]);

			return result;
		}

		// Compare operators

		/// Compare operator. Is equal.
		///
		/// \param[in] other Other matrix
		/// \return True if equal, otherwise false
		bool operator==(const Matrix<T, 3, 3> & other) const
		{
			if (this->m_data[0] != other.m_data[0]
				|| this->m_data[1] != other.m_data[1]
				|| this->m_data[2] != other.m_data[2])
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
		Matrix<T, 3, 3> operator+(const Matrix<T, 2, 2> & other) const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = this->m_data[0][0] + other[0][0];
			result[0][1] = this->m_data[0][1] + other[0][1];
			result[1][0] = this->m_data[1][0] + other[1][0];
			result[1][1] = this->m_data[1][1] + other[1][1];
			return result;
		}

		/// Subtract other matrix.
		///
		/// \param[in] other Matrix to subtract
		/// \return Subtracted matrix
		Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2> & other) const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = this->m_data[0][0] - other[0][0];
			result[0][1] = this->m_data[0][1] - other[0][1];
			result[1][0] = this->m_data[1][0] - other[1][0];
			result[1][1] = this->m_data[1][1] - other[1][1];
			return result;
		}

		/// Multiply by scalar.
		///
		/// \param[in] scalar Scalar
		/// \return Multiplied vector
		Matrix<T, 2, 2> operator*(T scalar) const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = this->m_data[0][0] * scalar;
			result[0][1] = this->m_data[0][1] * scalar;
			result[1][0] = this->m_data[1][0] * scalar;
			result[1][1] = this->m_data[1][1] * scalar;
			return result;
		}

		/// Multiply by vector.
		///
		/// \param[in] vector Vector to multiply with
		/// \return Multiplied vector
		Vector<T, 2> operator*(const Vector<T, 2> & vector) const
		{
			Vector<T, 2> result;
			result[0] = this->m_data[0][0] * vector[0] + this->m_data[1][0] * vector[1];
			result[1] = this->m_data[0][1] * vector[0] + this->m_data[1][1] * vector[1];
			return result;
		}

		/// Divide by scalar.
		///
		/// \param[in] scalar Scalar
		/// \return Divided matrix
		Matrix<T, 2, 2> operator/(T scalar) const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = this->m_data[0][0] / scalar;
			result[0][1] = this->m_data[0][1] / scalar;
			result[1][0] = this->m_data[1][0] / scalar;
			result[1][1] = this->m_data[1][1] / scalar;
			return result;
		}

		/// Multiply by matrix.
		///
		/// \param[in] other Matrix to multiply with
		/// \return Multiplied matrix
		template<size_t W2>
		Matrix<T, 2, W2> operator*(const Matrix<T, W2, 2> &other) const
		{
			Matrix<T, 2, W2> result;

			for (size_t i = 0; i < 2; i++)
			{
				for (size_t j = 0; j < W2; j++)
				{
					double val = 0;
					for (size_t k = 0; k < 2; k++)
					{
						val += this->m_data[k][i] * other[j][k];
					}
					result[j][i] = val;
				}
			}

			return result;
		}

		// Matrix operations

		/// Get transposed matrix.
		///
		/// \return Transposed matrix
		Matrix<T, 2, 2> transposed() const
		{
			Matrix<T, 2, 2> result;
			result[0][0] = this->m_data[0][0];
			result[0][1] = this->m_data[1][0];
			result[1][0] = this->m_data[0][1];
			result[1][1] = this->m_data[1][1];
			return result;
		}

		/// Calculate determinant.
		///
		/// \return Determinant
		constexpr T determinant() const
		{
			return this->m_data[0][0] * this->m_data[1][1] - this->m_data[1][0] * this->m_data[0][1];
		}

		/// Calculate inverse of matrix.
		///
		/// \throw std::out_of_range Matrix has no inverse
		/// \return Inverse of matrix
		Matrix<T, 2, 2> inverse() const
		{
			const T det = determinant();
			if (det == 0)
			{
				throw std::out_of_range("Matrix has no inverse (matrix is singular)");
			}

			Matrix<T, 2, 2> result;
			result[0][0] = this->m_data[1][1] / det;
			result[0][1] = -this->m_data[0][1] / det;
			result[1][0] = -this->m_data[1][0] / det;
			result[1][1] = this->m_data[0][0] / det;
			return result;
		}
	};
}

#endif // SPATIUMGL_MATRIX2X2_H
