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
		Vector<T, H>& operator[](size_t index)
		{
			return m_data[index];
		}

		/// Access column (vector) by const reference.
		///
		/// \return Column const reference
		const Vector<T, H>& operator[](size_t index) const
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

		Vector<T, H> m_data[W];
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
		Matrix<T2, W, H> staticCast(const Matrix<T, W, H>& other) const
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

/* OLD
namespace spatiumgl {

	/// \class MatrixT
	/// \brief Matrix with fixed size and type.
	///
	/// Matrix is a class to represent a mathematical matrix, i.e. a 2D array
	/// defined by a number of rows and columns. The content of the matrix is
	/// stored in column-major format.
	template<typename T, size_t W, size_t H>
	class MatrixT
	{
	public:
		/// Constructor
		MatrixT()
			: m_data()
		{
		}

		/// Constructor
		///
		 /// \param[in] array 2D Initializer list (row-major)
		MatrixT(std::initializer_list<std::initializer_list<T>> array)
			: m_data()
		{
			// Set values
			auto colIt = array.begin();
			size_t col = 0;
			while (colIt != array.end() && col < W)
			{
				auto rowIt = colIt->begin();
				size_t row = 0;
				while (rowIt != colIt->end() && row < H)
				{
					operator[](col).operator[](row) = *rowIt;

					++rowIt;
					++row;
				}

				++colIt;
				++col;
			}
		}

		/// Compare operator. Is equal.
		///
		/// \param[in] other Other matrix
		/// \return True if equal, otherwise false
		bool operator==(const MatrixT<T,W,H> & other) const
		{
			// Compare elements
			for (size_t row = 0; row < H; row++)
			{
				for (size_t col = 0; col < W; col++)
				{
					if (operator[](col)[row] != other[col][row])
					{
						return false;
					}
				}
			}

			return true;
		}

		/// Compare operator. Is unequal.
		///
		/// \param[in] other Other matrix
		/// \return True if unequal, otherwise false
		bool operator!=(const MatrixT<T, W, H> &other) const
		{
			return !(operator ==(other));
		}

		// Access operators

		/// Access element by reference.
		///
		/// \param[in] col Column of element
		/// \throw std::out_of_range Matrix element out of range
		/// \return Element reference
		VectorT<T, H>& operator[](size_t col)
		{
			if (col >= W)
			{
				throw std::out_of_range("Matrix element index out of range");
			}
			return m_data[col];
		}

		/// Access element by const reference.
		///
		/// \param[in] col Column of element
		/// \throw std::out_of_range Matrix element out of range
		/// \return Element reference
		const VectorT<T, H>& operator[](size_t col) const
		{
			if (col >= W)
			{
				throw std::out_of_range("Matrix element index out of range");
			}
			return m_data[col];
		}

		// Arithmetic operators

		/// Add by matrix.
		///
		/// \param[in] other Matrix to add
		/// \return Added matrix
		MatrixT<T, W, H> operator+(const MatrixT<T, W, H>& other) const
		{
			// Add
			MatrixT<T, W, H> result;
			for (size_t row = 0; row < H; row++)
			{
				for (size_t col = 0; col < W; col++)
				{
					result[col][row] = operator[](col)[row] + other[col][row];
				}
			}
			return result;
		}

		/// Subtract by matrix.
		///
		/// \param[in] other Matrix to subtract
		/// \return Subtracted matrix
		MatrixT<T, W, H> operator-(const MatrixT<T,W,H>& other) const
		{
			// Subtract
			MatrixT<T, W, H> result;
			for (size_t row = 0; row < H; row++)
			{
				for (size_t col = 0; col < W; col++)
				{
					result[col][row] = operator[](col)[row] - other[col][row];
				}
			}
			return result;
		}

		/// Multiply by matrix.
		///
		/// \param[in] other Matrix to multiply with
		/// \return Multiplied matrix
		template<size_t W2>
		MatrixT<T, W2, H> operator*(const MatrixT<T,W2,W>& other) const
		{
			// Multiply
			MatrixT<T, W2, H> result;
			for (size_t i = 0; i < H; i++)
			{
				for (size_t j = 0; j < W2; j++)
				{
					T val = 0;
					for (size_t k = 0; k < W; k++)
					{
						val += operator[](k)[i] * other[j][k];
					}
					result[j][i] = val;
				}
			}
			return result;
		}

		/// Multiply by vector.
		///
		/// \param[in] other Vector to multiply with
		/// \return Multiplied vector
		VectorT<T, W> operator*(const VectorT<T, W> &vector) const
		{
			// Multiply
			VectorT<T, W> result;
			for (size_t row = 0; row < W; row++)
			{
				T val = 0;
				for (size_t col = 0; col < W; col++)
				{
					val += operator[](col).operator[](row) * vector[row];
				}
				result[row] = val;
			}
			return result;
		}

		/// Get transposed matrix.
		///
		/// \return Transposed matrix
		MatrixT<T, H, W> transposed() const
		{
			MatrixT<T, H, W> result;
			for (size_t col = 0; col < W; col++)
			{
				const VectorT<T, H> &column = operator[](col);
				for (size_t row = 0; row < H; row++)
				{
					result[row][col] = column[row];
				}
			}
			return result;
		}

		/// Get pointer to data.
		///
		/// The data is stored in colunmn-major format.
		///
		/// \return Data pointer
		T* data()
		{
			return m_data[0].data();
		}

		/// Clear all matrix elements.
		void clear()
		{
			for (size_t col = 0; col < W; col++)
			{
				VectorT<T, H> &column = m_data[col];
				for (size_t row = 0; row < H; row++)
				{
					column[row] = 0;
				}
			}
		}

		/// Output to ostream
		friend std::ostream& operator<<(std::ostream& os, const MatrixT<T, W, H>& matrix)
		{
			os << "(";
			if (W > 0) {
				os << matrix[0];
			}
			for (size_t i = 1; i < W; i++)
			{
				os << ", " << matrix[i];
			}
			os << ")";
			return os;
		}

	protected:
		std::array<VectorT<T,H>, W> m_data;
	};

	/// \class MatrixT
	/// \breif Matrix with sqaure size and fixed type.
	template<typename T, size_t N>
	class MatrixTN : public MatrixT<T, N, N>
	{
	public:
		/// Default constructor
		MatrixTN()
			: MatrixT()
		{
			//for (size_t i = 0; i < N; i++)
			//{
			//	m_data[i][i] = 1;
			//}
		}

		/// Constructor
		///
		/// \param[in] diagonal Diagonal value (use 1 for identity)
		MatrixTN(T diagonal)
			: MatrixT()
		{
			for (size_t i = 0; i < N; i++)
			{
				m_data[i][i] = 1;
			}
		}

		/// Constructor
		///
		/// \param[in] array 2D Initializer list (row-major)
		MatrixTN(std::initializer_list<std::initializer_list<T>> array)
			: MatrixT(array)
		{
		}

		/// Copy constructor
		///
		/// \param[in] vector Vector
		constexpr MatrixTN(const MatrixT<T, N, N> &matrix) // constexpr?
			: MatrixT<T, N, N>(matrix)
		{
		}
	};

	/// \class MatrixT2
	/// \breif Matrix with size 2x2 and fixed type.
	template<typename T>
	class MatrixT2 : public MatrixTN<T, size_t(2)>
	{

		// Rotation

	};

	/// \class MatrixT3
	/// \breif Matrix with size 3x3 and fixed type.
	template<typename T>
	class MatrixT3 : public MatrixTN<T, size_t(3)>
	{
	public:
		/// Default constructor
		///
		/// Identity matrix
		MatrixT3()
			: MatrixTN()
		{
		}

		/// Constructor
		///
		/// \param[in] array 2D Initializer list (row-major)
		MatrixT3(std::initializer_list<std::initializer_list<T>> array)
			: MatrixTN(array)
		{
		}

		// Rotation

	};

	/// \class MatrixT4
	/// \breif Matrix with size 4x4 and fixed type.
	template<typename T>
	class MatrixT4 : public MatrixTN<T, size_t(4)>
	{
	public:
		/// Default constructor
		///
		/// Identity matrix
		MatrixT4()
			: MatrixTN()
		{
		}

		/// Constructor
		///
		/// \param[in] diagonal Diagonal value (use 1 for identity)
		MatrixT4(T diagonal)
			: MatrixTN(diagonal)
		{
		}

		/// Copy constructor
		///
		/// \param[in] vector Vector
		constexpr MatrixT4(const MatrixTN<T, 4> &matrix) // constexpr?
			: MatrixTN<T, 4>(matrix)
		{
		}

		// Translation

		// Projection

	};

	template<size_t N>
	using MatrixN = MatrixTN<SPATIUMGL_PRECISION,N>;

	using Matrix2 = MatrixT2<SPATIUMGL_PRECISION>;
	using Matrix3 = MatrixT3<SPATIUMGL_PRECISION>;
	using Matrix4 = MatrixT4<SPATIUMGL_PRECISION>;

} // namespace spatiumgl
*/

#endif // SPATIUMGL_MATRIX_H