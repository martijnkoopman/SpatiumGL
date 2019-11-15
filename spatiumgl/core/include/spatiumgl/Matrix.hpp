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

#include "spatiumglexport.hpp"
#include "Vector.hpp"

#include <ostream>

namespace spatiumgl
{
	template<typename T, size_t W, size_t H>
	struct SPATIUMGL_EXPORT MatrixBase
	{
	public:
		/// Access column (vector) by reference.
		///
		/// \return Column reference
    Vector<T, H>& operator[](const size_t index)
		{
			return m_data[index];
		}

		/// Access column (vector) by const reference.
		///
		/// \return Column const reference
    const Vector<T, H>& operator[](const size_t index) const
		{
			return m_data[index];
		}

		/// Get number of columns (width)
		///
		/// \return Column count
		constexpr size_t cols() const noexcept
		{
			return W;
		}

		/// Get number of rows (height)
		///
		/// \return Row count
		constexpr size_t rows() const noexcept
		{
			return H;
		}

		/// Get pointer to data.
		///
		/// \return Data pointer
		T* data() noexcept
		{
			return m_data[0].data();
		}

		/// Get const pointer to data.
		///
		/// \return Const data pointer
		const T* data() const noexcept
		{
			return m_data[0].data();
		}

		/// Clear all values (set to 0).
		void clear()
		{
			// ERROR: std::fill(std::begin(m_data), std::end(m_data), 0);
		}

	protected:
		// Hide constructor to prevent declaration
		MatrixBase()
			: m_data()
		{}

		MatrixBase(std::initializer_list<std::initializer_list<T>> data)
			: m_data()
		{
			// Iterate columns
			size_t col = 0;
			auto colIt = data.begin();
			while (col < W && colIt != data.end())
			{
				Vector<T, H>& column = m_data[col];

				// Iterate rows
				size_t row = 0;
				auto rowIt = colIt->begin();
				while (row < H && rowIt != colIt->end())
				{
					// Copy value
					column[row] = *rowIt;

					++row;
					++rowIt;
				}

				++col;
				++colIt;
			}
		}

    Vector<T, H> m_data[W]; /// \todo std::array
	};

	/// \class Matrix
	///
	/// Internally a matrix is stored as an array of column vectors.
	/// 
	/// Example layout:
	/// | 00 04 08 12 |
	/// | 01 05 09 13 |
	/// | 02 06 10 14 |
	/// | 03 07 11 15 |
	/// 
	///  Memory layout:
	/// [00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15]
	///
	/// Element access:
	/// matrix[col][row] returns a reference or value (if matrix is const).
	///
	/// Fast iteration over a matrix:
	/// Matrix<T,W,H> matrix;
	/// for (size_t col = 0; col < W; col++)
	/// {
	///   Vector<T,H> &column = matrix[col]; // reference to column vector
	///	  for (size_t row = 0; row < H; row++)
	///   {
	///     T& val = column[row]; // reference to element
	///     // Do something with val...
	///   }
	/// }
	template<typename T, size_t W, size_t H>
	struct SPATIUMGL_EXPORT Matrix : public MatrixBase<T, W, H>
	{
		constexpr Matrix() = default;

		/// \TODO Add all matrix functionality that is also in Matrix2, Matrix3 and Matrix4

		template<typename T2>
    Matrix<T2, W, H> staticCast() const
		{
			Matrix<T2, W, H> result;

			for (size_t col = 0; col < W; col++)
			{
				const Vector<T, H>& columnIn = this->m_data[col];
				Vector<T, H>& columnOut = result[col];

				for (size_t row = 0; row < H; row++)
				{
					columnOut[row] = static_cast<T2>(columnIn[row]);
				}
			}

			return result;
		}

		/// Output to ostream (untested)
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, W, H>& matrix)
		{
			os << "Matrix(" << W << ", " << H << ")" << "\n";
			for (size_t row = 0; row < H; row++)
			{
				for (size_t col = 0; col < W; col++)
				{
					os << matrix[col][row] << " ";
				}
				os << "\n";
			}
			return os;
		}
	};
}

#include "Matrix2x2.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"

namespace spatiumgl
{
	using Matrix2 = Matrix<double, 2, 2>;
	using Matrix3 = Matrix<double, 3, 3>;
	using Matrix4 = Matrix<double, 4, 4>;

	using Matrix2f = Matrix<float, 2, 2>;
	using Matrix3f = Matrix<float, 3, 3>;
	using Matrix4f = Matrix<float, 4, 4>;
}

#endif // SPATIUMGL_MATRIX_H
