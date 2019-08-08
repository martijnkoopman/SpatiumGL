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

// Precision
#ifndef SPATIUMGL_SINGLE_PRECISION
#define SPATIUMGL_PRECISION double
#else
#define SPATIUMGL_PRECISION float
#endif

#include <cstddef> // std::size_t
#include <array> // std::array
#include <vector> // std::vector

namespace spatiumgl {

	/// \class VectorT
	/// \brief Fixed type and fixed size vector
	template<typename T, size_t N>
	class VectorT
	{
	public:
		VectorT()
			: m_data()
		{}
		// Override operators:
		// +
		// -
		// *
		// 

	protected:
		std::array<T, N> m_data;
	};

	template<typename T>
	class VectorT2 : public VectorT<T, 2>
	{
	public:
		VectorT2(const T& x, const T& y)
			: VectorT<T, 2>()
		{
			m_data[0] = x;
			m_data[1] = y;
		}

		void setX(const T& x)
		{
			m_data[0] = x;
		}

		T x() const
		{
			return m_data[0];
		}

		void setY(const T& x)
		{
			m_data[1] = y;
		}

		T y() const
		{
			return m_data[1];
		}
	};

	template<typename T>
	class VectorT3 : public VectorT<T, 3>
	{
	public:
		VectorT3(const T& x, const T& y, const T& z)
			: VectorT<T, 3>()
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
		}

		void setX(const T& x)
		{
			m_data[0] = x;
		}

		T x() const
		{
			return m_data[0];
		}

		void setY(const T& x)
		{
			m_data[1] = y;
		}

		T y() const
		{
			return m_data[1];
		}

		void setZ(const T& z)
		{
			m_data[2] = z;
		}

		T z() const
		{
			return m_data[2];
		}
	};

	template<typename T>
	class VectorT4 : public VectorT<T, 4>
	{
	public:
		VectorT4(const T& x, const T& y, const T& z, const T& w)
			: VectorT<T, 4>()
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
			m_data[3] = w;
		}

		void setX(const T& x)
		{
			m_data[0] = x;
		}

		T x() const
		{
			return m_data[0];
		}

		void setY(const T& x)
		{
			m_data[1] = y;
		}

		T y() const
		{
			return m_data[1];
		}

		void setZ(const T& z)
		{
			m_data[2] = z;
		}

		T z() const
		{
			return m_data[2];
		}

		void setW(const T& w)
		{
			m_data[3] = w;
		}

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

	/// \class Vector
	/// \brief Arbitrarily size vector
	class Vector
	{
	public:
		Vector()
		{
			// Do stuff
		}

	protected:
		std::vector<SPATIUMGL_PRECISION> m_data;
	};

} // namespace spatiumgl

#endif // SPATIUMGL_VECTOR_H