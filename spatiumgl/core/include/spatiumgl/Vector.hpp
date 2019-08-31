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

#ifndef SPATIUMGL_VECTOR_H
#define SPATIUMGL_VECTOR_H

#include "spatiumglexport.hpp"

// Precision
#ifndef SPATIUMGL_SINGLE_PRECISION
#define SPATIUMGL_PRECISION double
#else
#define SPATIUMGL_PRECISION float
#endif

#include <cstddef> // std::size_t
#include <initializer_list> // std::initializer_list
#include <ostream> // std::ostream

namespace spatiumgl
{
	/// \class VectorBase
	/// \brief Vector base class
	///
	/// Cannot be declared directly, only inherited.
	template<typename T, size_t N>
	struct SPATIUMGL_EXPORT VectorBase
	{
	public:
		/// Access element by reference.
		/// 
		/// \param[in] index Index of element
		/// \return Element reference
		T& operator[](size_t index)
		{
			return m_data[index];
		}

		/// Access element by const reference.
		/// 
		/// \param[in] index Index of element
		/// \return Element const reference
		const T& operator[](size_t index) const
		{
			return m_data[index];
		}

		/// Get number of elements in the vector.
		///
		/// \return Number of elements.
		constexpr size_t size() const noexcept
		{
			return N;
		}

		/// Get pointer to data.
		///
		/// \return Data pointer
		T* data() noexcept
		{
			return &m_data;
		}

		/// Get const pointer to data.
		///
		/// \return Const data pointer
		const T* data() const noexcept
		{
			return &m_data[0];
		}

		/// Clear all values (set to 0).
		void clear()
		{
			// ERROR?: std::fill(std::begin(m_data), std::end(m_data), 0);
		}

	protected:
		/// Default constructor
		constexpr VectorBase()
			: m_data{ 0 }
		{}

		//// Constructor
		//constexpr VectorBase(std::initializer_list<T> data)
		//	: m_data{ 0 }
		//{
		//	// Copy values
		//	size_t i = 0;
		//	auto it = data.begin();
		//	while(i < N && it != data.end())
		//	{
		//		m_data[i] = *it;

		//		++i;
		//		++it;
		//	}
		//}

		T m_data[N];
	};

	/// \class Vector
	/// \brief Arbitrary fixed size vector
	template<typename T, size_t N>
	struct SPATIUMGL_EXPORT Vector : public VectorBase<T, N>
	{
		/// Default constructor
		constexpr Vector() = default;

		/// Compare operator. Is equal.
		///
		/// \param[in] other Other vector
		/// \return True if equal, otherwise false
		bool operator==(const Vector<T,N> &other) const
		{
			// Compare elements
			for (size_t i = 0; i < N; i++)
			{
				if (m_data[i] != other.m_data[i])
				{
					return false;
				}
			}

			return true;
		}

		/// Compare operator. Is unequal.
		///
		/// \param[in] other Other vector
		/// \return True if unequal, otherwise false
		bool operator!=(const Vector<T, N> &other) const
		{
			return !(operator ==(other));
		}

		//// Arithmetic operators:

		///// Add another vector.
		/////
		///// \param[in] other Vector to add
		///// \return Added vector
		//Vector<T, N> operator+(const Vector<T, N>& other) const
		//{
		//	VectorT<T, N> result;
		//	for (size_t row = 0; row < N; row++)
		//	{
		//		result[row] = operator[](row) + other[row];
		//	}
		//	return result;
		//}

		// ...
	};
}

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace spatiumgl
{
	using Vector2i = Vector<int, 2>;
	using Vector2 = Vector<SPATIUMGL_PRECISION, 2>;
	using Vector3 = Vector<SPATIUMGL_PRECISION, 3>;
	using Vector4 = Vector<SPATIUMGL_PRECISION, 4>;
}

/* OLD
namespace spatiumgl {

	/// \class VectorT
	/// \brief Fixed type and fixed size vector.
	template<typename T, size_t N>
	class VectorT
	{
	public:
		/// Default constructor
		VectorT()
			: m_data()
		{}

		/// Constructor
		///
		/// \param[in] arr Initializer list
		VectorT(std::initializer_list<T> arr)
			: m_data()
		{
			// Copy values
			auto rowIt = arr.begin();
			auto dataIt = m_data.begin();
			while (rowIt != arr.end() && dataIt != m_data.end())
			{
				*dataIt = *rowIt;

				++rowIt;
				++dataIt;
			}
		}

		// Access operators

		/// Get pointer to data.
		///
		/// \return Data pointer
		T* data()
		{
			return m_data.data();
		}

		/// Access element by value.
		///
		/// \param[in] row Row of element
		/// \throw std::out_of_range Matrix element out of range
		/// \return Element value
		T operator[] (size_t row) const
		{
			if (row >= N)
			{
				throw std::out_of_range("Vector element out of range");
			}
			return m_data[row];
		}

		/// Access element by reference.
		///
		/// \param[in] row Row of element
		/// \param[in] col Column of element
		/// \throw std::out_of_range Matrix element out of range
		/// \return Element reference
		T& operator[] (size_t row)
		{
			if (row >= N)
			{
				throw std::out_of_range("Vector element out of range");
			}
			return m_data[row];
		}

		// Arithmetic operators:

		/// Add another vector.
		///
		/// \param[in] other Vector to add
		/// \return Added vector
		VectorT<T, N> operator+(const VectorT<T,N> &other) const
		{
			VectorT<T, N> result;
			for (size_t row = 0; row < N; row++)
			{
				result[row] = operator[](row) + other[row];
			}
			return result;
		}

		/// Subtract other vector.
		///
		/// \param[in] other Vector to subtract
		/// \return Subtracted vector
		VectorT<T, N> operator-(const VectorT<T, N>& other) const
		{
			VectorT<T, N> result;
			for (size_t row = 0; row < N; row++)
			{
				result[row] = operator[](row) - other[row];
			}
			return result;
		}

		/// Multiply by scalar.
		///
		/// \param[in] scalar Scalar
		/// \return Multiplied vector
		VectorT<T, N> operator*(T scalar) const
		{
			VectorT<T, N> result;
			for (size_t row = 0; row < N; row++)
			{
				result[row] += operator[](row) * scalar;
			}
			return result;
		}

		/// Divide by scalar.
		///
		/// \param[in] scalar Scalar
		/// \return Divided vector
		VectorT<T, N> operator/(T scalar) const
		{
			VectorT<T, N> result;
			for (size_t row = 0; row < N; row++)
			{
				result[row] += operator[](row) / scalar;
			}
			return result;
		}

		// ...

		/// Calculate length of vector (magnitude, euclidean).
		///
		/// \return Length
		T length() const
		{
			T result = 0;
			for (size_t row = 0; row < N; row++)
			{
				T val = m_data[row];
				result += val * val;
			}
			return sqrt(result);
		}

		/// Normalize the vector.
		/// A normalized vector has length = 1.
		void normalize()
		{
			T l = length();
			for (size_t row = 0; row < N; row++)
			{
				T val = m_data[row];
				m_data[row] = val / l;
			}
		}

		/// Get normalized copy of vector.
		/// A normalized vector has length = 1.
		///
		/// \return Normalized vector
		VectorT<T, N> normalized() const
		{
			T l = length();

			VectorT<T, N> result;
			for (size_t row = 0; row < N; row++)
			{
				result[row] = m_data[row] / l;
			}
			return result;
		}

		// Geometric operations:

		/// Calculate dot product with vector.
		/// Dot product = 0: vectors are orthogonal (perpendicular).
		/// Dot product = |a||b| (1 if normalized): vectors are parallel.
		///
		/// \param[in] other Other vector
		/// \return Dot product
		T dot(const VectorT<T, N>& other) const
		{
			T result = 0;
			for (size_t row = 0; row < N; row++)
			{
				result += operator[](row) + other[row];
			}
			return result;
		}

		/// Calculate angle with vector.
		///
		/// \param[in] other Other vector
		/// \return Angle in radians
		T angle(const VectorT<T, N>& other) const
		{
			return acos((this->dot(other)) / (this->length() * other.length()));
		}

		/// Project vector onto vector.
		///
		/// \param[in] other Vector to project
		/// \return Projected vector
		VectorT<T, N> project(const VectorT<T, N>& other) const
		{
			return this->normalized() * (other.dot(*this) / this->length());
		}

		/// Output to ostream
		friend std::ostream& operator<<(std::ostream& os, const VectorT<T, N>& vector)
		{
			os << "(";
			if (N > 0) {
				os << vector[0];
			}
			for (size_t i = 1; i < N; i++)
			{
				os << ", " << vector[i];
			}
			os << ")";
			return os;
		}

	protected:
		std::array<T, N> m_data;
	};

	/// \class VectorT2
	/// \brief Vector with 2 elements.
	///
	/// The 2 elements are accessible as x and y.
	template<typename T>
	class VectorT2 : public VectorT<T, size_t(2)>
	{
	public:
		/// Default constructor
		VectorT2()
			: VectorT<T, 2>()
		{
			m_data[0] = 0;
			m_data[1] = 0;
		}

		/// Constructor
		///
		/// \param[in] x X value
		/// \param[in] y Y value
		VectorT2(const T& x, const T& y)
			: VectorT<T, 2>()
		{
			m_data[0] = x;
			m_data[1] = y;
		}

		/// Copy constructor
		///
		/// \param[in] vector Vector
		constexpr VectorT2(const VectorT<T, size_t(2)>& vector) // constexpr?
			: VectorT<T, 2>(vector)
		{
		}

		/// Set X value.
		///
		/// \param[in] x X value
		void x(const T& x)
		{
			m_data[0] = x;
		}

		/// Get X value.
		///
		/// \return X value
		T x() const
		{
			return m_data[0];
		}

		/// Get X value by reference
		///
		/// \return X value reference
		T& x()
		{
			return m_data[0];
		}

		/// Set Y value.
		///
		/// \param[in] y Y value
		void y(const T& x)
		{
			m_data[1] = y;
		}

		/// Get Y value.
		///
		/// \return Y value
		T y() const
		{
			return m_data[1];
		}

		/// Get Y value by reference
		///
		/// \return Y value reference
		T& y()
		{
			return m_data[1];
		}
	};

	/// \class VectorT3
	/// \brief Vector with 3 elements.
	///
	/// The 3 elements are accessible as x, y and z.
	template<typename T>
	class VectorT3 : public VectorT<T, size_t(3)>
	{
	public:
		/// Default constructor
		VectorT3()
			: VectorT<T, 3>()
		{
		}

		/// Constructor
		///
		/// \param[in] x X value
		/// \param[in] y Y value
		/// \param[in] z Z value
		VectorT3(const T& x, const T& y, const T& z)
			: VectorT<T, 3>()
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
		}

		/// Constructor
		///
		/// \param[in] xy Vector with X and Y value
		/// \param[in] z Z value
		VectorT3(const VectorT2<T> &xy, const T& z)
			: VectorT<T, 3>()
		{
			m_data[0] = xy.x();
			m_data[1] = xy.y();
			m_data[2] = z;
		}

		/// Copy constructor
		///
		/// \param[in] vector Vector
		constexpr VectorT3(const VectorT<T, size_t(3)>& vector) // constexpr?
			: VectorT<T, 3>(vector)
		{
		}

		/// Set X value.
		///
		/// \param[in] x X value
		void x(const T& x)
		{
			m_data[0] = x;
		}

		/// Get X value.
		///
		/// \return X value
		T x() const
		{
			return m_data[0];
		}

		/// Set Y value.
		///
		/// \param[in] y Y value
		void y(const T& y)
		{
			m_data[1] = y;
		}

		/// Get Y value.
		///
		/// \return Y value
		T y() const
		{
			return m_data[1];
		}

		/// Set Z value.
		///
		/// \param[in] z Z value
		void z(const T& z)
		{
			m_data[2] = z;
		}

		/// Get Z value.
		///
		/// \return Z value
		T z() const
		{
			return m_data[2];
		}

		// Geometric operations:

		/// Calculate cross product with vector.
		/// The cross product is perpendicular to the two input vectors.
		/// The result can be NaN.
		///
		/// \param[in] other Other vector
		/// \return Cross product
		VectorT3 cross(const VectorT3& other) const
		{
			VectorT3 result;
			result.x(y() * other.z() - z() * other.y());
			result.y(z() * other.x() - x() * other.z());
			result.z(x() * other.y() - y() * other.x());
			return result;
		}
	};

	/// \class VectorT4
	/// \brief Vector with 4 elements.
	///
	/// The 4 elements are accessible as x, y, z and w.
	template<typename T>
	class VectorT4 : public VectorT<T, size_t(4)>
	{
	public:
		/// Default constructor
		VectorT4()
			: VectorT<T, 4>()
		{
		}

		/// Constructor
		///
		/// \param[in] x X value
		/// \param[in] y Y value
		/// \param[in] z Z value
		/// \param[in] w W value
		VectorT4(const T& x, const T& y, const T& z, const T& w)
			: VectorT<T, 4>()
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
			m_data[3] = w;
		}

		/// Constructor
		///
		/// \param[in] xyz Vector with X, Y and Z value
		/// \param[in] w W value
		VectorT4(const VectorT3<T> &xyz, const T& w)
			: VectorT<T, 4>()
		{
			m_data[0] = xyz.x();
			m_data[1] = xyz.y();
			m_data[2] = xyz.z();
			m_data[3] = w;
		}

		/// Copy constructor
		///
		/// \param[in] vector Vector
		constexpr VectorT4(const VectorT<T, size_t(4)>& vector) // constexpr?
			: VectorT<T, 4>(vector)
		{
		}

		/// Set X value.
		///
		/// \param[in] x X value
		void x(const T& x)
		{
			m_data[0] = x;
		}

		/// Get X value.
		///
		/// \return X value
		T x() const
		{
			return m_data[0];
		}

		/// Set Y value.
		///
		/// \param[in] y Y value
		void y(const T& x)
		{
			m_data[1] = y;
		}

		/// Get Y value.
		///
		/// \return Y value
		T y() const
		{
			return m_data[1];
		}

		/// Set Z value.
		///
		/// \param[in] z Z value
		void z(const T& z)
		{
			m_data[2] = z;
		}

		/// Get Z value.
		///
		/// \return Z value
		T z() const
		{
			return m_data[2];
		}

		/// Set W value.
		///
		/// \param[in] w W value
		void w(const T& w)
		{
			m_data[3] = w;
		}

		/// Get W value.
		///
		/// \return W value
		T w() const
		{
			return m_data[3];
		}
	};

	using Vector2i = VectorT2<int>;
	using Vector3i = VectorT3<int>;
	using Vector4i = VectorT4<int>;
	using Vector2 = VectorT2<SPATIUMGL_PRECISION>;
	using Vector3 = VectorT3<SPATIUMGL_PRECISION>;
	using Vector4 = VectorT4<SPATIUMGL_PRECISION>;
} // namespace spatiumgl
*/

#endif // SPATIUMGL_VECTOR_H