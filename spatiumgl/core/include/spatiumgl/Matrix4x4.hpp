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

#ifndef SPATIUMGL_MATRIX4X4_H
#define SPATIUMGL_MATRIX4X4_H

#include "Matrix.hpp"

namespace spatiumgl
{
	template<typename T>
	struct SPATIUMGL_EXPORT Matrix<T, 4, 4> : public MatrixBase<T, 4, 4>
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
			m_data[2][2] = diagional;
			m_data[3][3] = diagional;
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
		bool operator==(const Matrix<T, 4, 4> & other) const
		{
			if (m_data[0] != other.m_data[0]
				|| m_data[1] != other.m_data[1]
				|| m_data[2] != other.m_data[2]
				|| m_data[3] != other.m_data[3])
			{
				return false;
			}
			return true;
		}

		/// Compare operator. Is unequal.
		///
		/// \param[in] other Other matrix
		/// \return True if unequal, otherwise false
		bool operator!=(const Matrix<T, 4, 4> & other) const
		{
			return !(operator ==(other));
		}

		// Arithmetic operators

		/// Add another matrix.
		///
		/// \param[in] other Matrix to add
		/// \return Added matrix
		Matrix<T, 4, 4> operator+(const Matrix<T, 4, 4> & other) const
		{
			Matrix<T, 4, 4> result;
			result[0][0] = m_data[0][0] + other[0][0];
			result[0][1] = m_data[0][1] + other[0][1];
			result[0][2] = m_data[0][2] + other[0][2];
			result[0][3] = m_data[0][3] + other[0][3];
			result[1][0] = m_data[1][0] + other[1][0];
			result[1][1] = m_data[1][1] + other[1][1];
			result[1][2] = m_data[1][2] + other[1][2];
			result[1][3] = m_data[1][3] + other[1][3];
			result[2][0] = m_data[2][0] + other[2][0];
			result[2][1] = m_data[2][1] + other[2][1];
			result[2][2] = m_data[2][2] + other[2][2];
			result[2][3] = m_data[2][3] + other[2][3];
			result[3][0] = m_data[3][0] + other[3][0];
			result[3][1] = m_data[3][1] + other[3][1];
			result[3][2] = m_data[3][2] + other[3][2];
			result[3][3] = m_data[3][3] + other[3][3];
			return result;
		}

		/// Subtract other matrix.
		///
		/// \param[in] other Matrix to subtract
		/// \return Subtracted matrix
		Matrix<T, 4, 4> operator-(const Matrix<T, 4, 4> & other) const
		{
			Matrix<T, 4, 4> result;
			result[0][0] = m_data[0][0] - other[0][0];
			result[0][1] = m_data[0][1] - other[0][1];
			result[0][2] = m_data[0][2] - other[0][2];
			result[0][3] = m_data[0][3] - other[0][3];
			result[1][0] = m_data[1][0] - other[1][0];
			result[1][1] = m_data[1][1] - other[1][1];
			result[1][2] = m_data[1][2] - other[1][2];
			result[1][3] = m_data[1][3] - other[1][3];
			result[2][0] = m_data[2][0] - other[2][0];
			result[2][1] = m_data[2][1] - other[2][1];
			result[2][2] = m_data[2][2] - other[2][2];
			result[2][3] = m_data[2][3] - other[2][3];
			result[3][0] = m_data[3][0] - other[3][0];
			result[3][1] = m_data[3][1] - other[3][1];
			result[3][2] = m_data[3][2] - other[3][2];
			result[3][3] = m_data[3][3] - other[3][3];
			return result;
		}

		/// Multiply by scalar.
		// TODO

		/// Multiply by vector.
		///
		/// \param[in] vector Vector to multiply with
		/// \return Multiplied vector
		constexpr Vector<T, 4> operator*(const Vector<T, 4> & vector) const
		{
			Vector<T, 4> result;
			result[0] = m_data[0][0] * vector[0] + m_data[1][0] * vector[1] + m_data[2][0] * vector[2] + m_data[3][0] * vector[3];
			result[1] = m_data[0][1] * vector[0] + m_data[1][1] * vector[1] + m_data[2][1] * vector[2] + m_data[3][1] * vector[3];
			result[2] = m_data[0][2] * vector[0] + m_data[1][2] * vector[1] + m_data[2][2] * vector[2] + m_data[3][2] * vector[3];
			result[3] = m_data[0][3] * vector[0] + m_data[1][3] * vector[1] + m_data[2][3] * vector[2] + m_data[3][3] * vector[3];
			return result;
		}

		/// Divide by scalar.
		// TODO

		// Matrix operations

		/// Get transposed matrix.
		///
		/// \return Transposed matrix
		constexpr Matrix<T, 3, 3> transposed() const
		{
			Matrix<T, 3, 3> result;
			result[0][0] = m_data[0][0];
			result[0][1] = m_data[1][0];
			result[0][2] = m_data[2][0];
			result[0][3] = m_data[3][0];
			result[1][0] = m_data[0][1];
			result[1][1] = m_data[1][1];
			result[1][2] = m_data[2][1];
			result[1][3] = m_data[3][1];
			result[2][0] = m_data[0][2];
			result[2][1] = m_data[1][2];
			result[2][2] = m_data[2][2];
			result[2][3] = m_data[3][2];
			result[3][0] = m_data[0][3];
			result[3][1] = m_data[1][3];
			result[3][2] = m_data[2][3];
			result[3][3] = m_data[3][3];
			return result;
		}

		/// Omit a given row and column.
		///
		/// \param[in] row Row to omit
		/// \param[out] col Column to omit
		/// \return Matrix with omitted row and column
		constexpr Matrix<T, 3, 3> omit(size_t col, size_t row) const
		{
			Matrix<T, 3, 3> result;
			size_t colCount = 0, rowCount = 0;
			for (size_t i = 0; i < 4; i++)
			{
				if (i != row)
				{
					colCount = 0;
					for (size_t j = 0; j < 4; j++)
					{
						if (j != col)
						{
							result[colCount][rowCount] = m_data[j][i];
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
			T det = 0;
			for (size_t i = 0; i < 4; i++)
			{
				Matrix<T, 3, 3> minor = omit(i, 0);
				det += (i % 2 == 1 ? -1.0 : 1.0) * m_data[i][0] * minor.determinant();
			}
			return det;
		}

		/// Calulcate minor
		///
		/// The minor is the determinant of the matrix formed by omitting a given
		/// row and column.
		///
		/// \param[in] row Row to omit
		/// \param[out] col Column to omit
		/// \return Minor
		constexpr T minor(size_t col, size_t row) const
		{
			const Matrix<T, 3, 3> t = omit(col, row);
			return t.determinant();
		}

		/// Calculate inverse of matrix.
		///
		/// \throw std::out_of_range Matrix has no inverse
		/// \return Inverse of matrix
		constexpr Matrix<T, 4, 4> inverse() const
		{
			const T det = determinant();
			if (det == 0)
			{
				throw std::out_of_range("Matrix has no inverse (matrix is singular)");
			}

			Matrix<T, 4, 4> result;
			for (size_t j = 0; j < 4; j++)
			{
				for (size_t i = 0; i < 4; i++)
				{
					Matrix<T, 3, 3> minor = omit(i, j);
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

		// Geometric operations

		static constexpr Matrix<T, 4, 4> perspective(T fovy, T aspect, T near, T far)
		{
			Matrix<T, 4, 4> result;
			// TODO: Compute fields
			return result;
		}
	};
}

#endif // SPATIUMGL_MATRIX4X4_H