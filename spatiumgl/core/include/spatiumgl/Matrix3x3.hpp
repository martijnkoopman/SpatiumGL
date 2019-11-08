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

#ifndef SPATIUMGL_MATRIX3X3_H
#define SPATIUMGL_MATRIX3X3_H

#include "Matrix.hpp"

#ifdef __linux__
#undef minor
#endif

namespace spatiumgl
{
	template<typename T>
	struct SPATIUMGL_EXPORT Matrix<T, 3, 3> : public MatrixBase<T, 3, 3>
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
			: MatrixBase<T, 3, 3>()
		{
			this->m_data[0][0] = diagional;
			this->m_data[1][1] = diagional;
			this->m_data[2][2] = diagional;
		}

		/// Constructor
		///
		/// \param[in] Data Initializer list with column-major ordering.
		Matrix(std::initializer_list<std::initializer_list<T>> data)
			: MatrixBase<T, 3, 3>(data)
		{
		}

		/// Cast to matrix with different element type (static_cast).
		///
		/// \return Matrix with cast element type
		template<typename T2>
		Matrix<T2, 3, 3> staticCast() const
		{
			Matrix<T2, 3, 3> result;

			// Column 0
			result[0][0] = static_cast<T2>(this->m_data[0][0]);
			result[0][1] = static_cast<T2>(this->m_data[0][1]);
			result[0][2] = static_cast<T2>(this->m_data[0][2]);

			// Column 1
			result[1][0] = static_cast<T2>(this->m_data[1][0]);
			result[1][1] = static_cast<T2>(this->m_data[1][1]);
			result[1][2] = static_cast<T2>(this->m_data[1][2]);

			// Column 2
			result[2][0] = static_cast<T2>(this->m_data[2][0]);
			result[2][1] = static_cast<T2>(this->m_data[2][1]);
			result[2][2] = static_cast<T2>(this->m_data[2][2]);

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
		Matrix<T, 3, 3> operator+(const Matrix<T, 3, 3> & other) const
		{
			Matrix<T, 3, 3> result;
			result[0][0] = this->m_data[0][0] + other[0][0];
			result[0][1] = this->m_data[0][1] + other[0][1];
			result[0][2] = this->m_data[0][2] + other[0][2];
			result[1][0] = this->m_data[1][0] + other[1][0];
			result[1][1] = this->m_data[1][1] + other[1][1];
			result[1][2] = this->m_data[1][2] + other[1][2];
			result[2][0] = this->m_data[2][0] + other[2][0];
			result[2][1] = this->m_data[2][1] + other[2][1];
			result[2][2] = this->m_data[2][2] + other[2][2];
			return result;
		}

		/// Subtract other matrix.
		///
		/// \param[in] other Matrix to subtract
		/// \return Subtracted matrix
		Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3> & other) const
		{
			Matrix<T, 3, 3> result;
			result[0][0] = this->m_data[0][0] - other[0][0];
			result[0][1] = this->m_data[0][1] - other[0][1];
			result[0][2] = this->m_data[0][2] - other[0][2];
			result[1][0] = this->m_data[1][0] - other[1][0];
			result[1][1] = this->m_data[1][1] - other[1][1];
			result[1][2] = this->m_data[1][2] - other[1][2];
			result[2][0] = this->m_data[2][0] - other[2][0];
			result[2][1] = this->m_data[2][1] - other[2][1];
			result[2][2] = this->m_data[2][2] - other[2][2];
			return result;
		}

		/// Multiply by scalar.
		///
		/// \param[in] scalar Scalar
		/// \return Multiplied vector
		Matrix<T, 3, 3> operator*(T scalar) const
		{
			Matrix<T, 3, 3> result;
			result[0][0] = this->m_data[0][0] * scalar;
			result[0][1] = this->m_data[0][1] * scalar;
			result[0][2] = this->m_data[0][2] * scalar;
			result[1][0] = this->m_data[1][0] * scalar;
			result[1][1] = this->m_data[1][1] * scalar;
			result[1][2] = this->m_data[1][2] * scalar;
			result[2][0] = this->m_data[2][0] * scalar;
			result[2][1] = this->m_data[2][1] * scalar;
			result[2][2] = this->m_data[2][2] * scalar;
			return result;
		}

		/// Multiply by vector.
		///
		/// \param[in] vector Vector to multiply with
		/// \return Multiplied vector
		Vector<T, 3> operator*(const Vector<T, 3> & vector) const
		{
			Vector<T, 3> result;
			result[0] = this->m_data[0][0] * vector[0] + this->m_data[1][0] * vector[1] + this->m_data[2][0] * vector[2];
			result[1] = this->m_data[0][1] * vector[0] + this->m_data[1][1] * vector[1] + this->m_data[2][1] * vector[2];
			result[2] = this->m_data[0][2] * vector[0] + this->m_data[1][2] * vector[1] + this->m_data[2][2] * vector[2];
			return result;
		}

		/// Divide by scalar.
		///
		/// \param[in] scalar Scalar
		/// \return Divided matrix
		Matrix<T, 3, 3> operator/(T scalar) const
		{
			Matrix<T, 3, 3> result;
			result[0][0] = this->m_data[0][0] / scalar;
			result[0][1] = this->m_data[0][1] / scalar;
			result[0][2] = this->m_data[0][2] / scalar;
			result[1][0] = this->m_data[1][0] / scalar;
			result[1][1] = this->m_data[1][1] / scalar;
			result[1][2] = this->m_data[1][2] / scalar;
			result[2][0] = this->m_data[2][0] / scalar;
			result[2][1] = this->m_data[2][1] / scalar;
			result[2][2] = this->m_data[2][2] / scalar;
			return result;
		}

		// Matrix operations

		/// Get transposed matrix.
		///
		/// \return Transposed matrix
		Matrix<T, 3, 3> transposed() const
		{
			Matrix<T, 3, 3> result;
			result[0][0] = this->m_data[0][0];
			result[0][1] = this->m_data[1][0];
			result[0][2] = this->m_data[2][0];
			result[1][0] = this->m_data[0][1];
			result[1][1] = this->m_data[1][1];
			result[1][2] = this->m_data[2][1];
			result[2][0] = this->m_data[0][2];
			result[2][1] = this->m_data[1][2];
			result[2][2] = this->m_data[2][2];
			return result;
		}

		/// Omit a given row and column.
		///
		/// \param[in] row Row to omit
		/// \param[out] col Column to omit
		/// \return Matrix with omitted row and column
		Matrix<T, 2, 2> omit(size_t col, size_t row) const
		{
			Matrix<T, 2, 2> result;
			size_t colCount = 0, rowCount = 0;
			for (size_t i = 0; i < 3; i++)
			{
				if (i != row)
				{
					colCount = 0;
					for (size_t j = 0; j < 3; j++)
					{
						if (j != col)
						{
							result[colCount][rowCount] = this->m_data[j][i];
							colCount++;
						}
					}
					rowCount++;
				}
			}

			return result;
		}

		/// Calculate determinant.
		///
		/// \return Determinant
		constexpr T determinant() const
		{
			return this->m_data[0][0] * (this->m_data[1][1] * this->m_data[2][2] - this->m_data[2][1] * this->m_data[1][2]) -
				this->m_data[1][0] * (this->m_data[0][1] * this->m_data[2][2] - this->m_data[2][1] * this->m_data[0][2]) +
				this->m_data[2][0] * (this->m_data[0][1] * this->m_data[1][2] - this->m_data[1][1] * this->m_data[0][2]);
		}

		/// Calulcate minor
		///
		/// The minor is the determinant of the matrix formed by omitting a given
		/// row and column.
		///
		/// \param[in] row Row to omit
		/// \param[out] col Column to omit
		/// \return Minor
		T minor(size_t col, size_t row) const
		{
			const Matrix<T, 2, 2> t = omit(col, row);
			return t.determinant();
		}

		/// Calculate inverse of matrix.
		///
		/// \throw std::out_of_range Matrix has no inverse
		/// \return Inverse of matrix
		Matrix<T, 3, 3> inverse() const
		{
			const T det = determinant();
			if (det == 0)
			{
				throw std::out_of_range("Matrix has no inverse (matrix is singular)");
			}

			Matrix<T, 3, 3> result;
			for (size_t j = 0; j < 3; j++)
			{
				for (size_t i = 0; i < 3; i++)
				{
					Matrix<T, 2, 2> minor = omit(i, j);
					const T r = minor.determinant() / det;
					result[j][i] = r;
					if ((i + j) % 2 == 1)
					{
						result[j][i] = -result[j][i];
					}
				}
			}
			return result;
		}
	};
}

#endif // SPATIUMGL_MATRIX3X3_H
