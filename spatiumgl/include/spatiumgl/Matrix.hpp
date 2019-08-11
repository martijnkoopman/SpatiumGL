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

	/// \class MatrixT
	/// \brief Matrix with fixed size and type.
	///
	/// Matrix is a class to represent a mathematical matrix, i.e. a 2D array
	/// defined by a number of rows and columns. The content of the matrix is
	/// stored in row-major format.
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
		
		// Access operators

		/// Access element by value.
		///
		/// \param[in] col Column of element
		/// \throw std::out_of_range Matrix element out of range
		/// \return Element value
		VectorT<T, H> operator[](size_t col) const
		{
			if (col >= W)
			{
				throw std::out_of_range("Matrix element index out of range");
			}
			return m_data[col];
		}

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

		// Arithmetic operators

		/// Get pointer to data.
		///
		/// The data is stored in row-major format.
		///
		/// \return Data pointer
		T* data()
		{
			return m_data[0].data();
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
		///
		/// Identity matrix
		MatrixTN()
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
		
		
		// Translation

		// Projection

	};

	template<size_t N>
	using MatrixN = MatrixTN<SPATIUMGL_PRECISION,N>;

	using Matrix2 = MatrixT2<SPATIUMGL_PRECISION>;
	using Matrix3 = MatrixT3<SPATIUMGL_PRECISION>;
	using Matrix4 = MatrixT4<SPATIUMGL_PRECISION>;

} // namespace spatiumgl

#endif // SPATIUMGL_MATRIX_H