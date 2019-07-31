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


namespace spatiumgl {

template<typename T, size_t N>
class Vector
{
	// Override operators:
	// +
	// -
	// *
	// 

protected:
	std::array<T, N> m_data;
};

template<typename T>
class Vector2 : public Vector<T, 2>
{
	void setX(const& T x)
	{
		m_data[0] = x;
	}

	T x() const
	{
		return m_data[0];
	}

	void setY(const& T x)
	{
		m_data[1] = y;
	}

	T y() const
	{
		return m_data[1];
	}
};

template<typename T>
class Vector3 : public Vector<T, 3>
{
	void setX(const& T x)
	{
		m_data[0] = x;
	}

	T x() const
	{
		return m_data[0];
	}

	void setY(const& T x)
	{
		m_data[1] = y;
	}

	T y() const
	{
		return m_data[1];
	}

	void setZ(const& T z)
	{
		m_data[2] = z;
	}

	T z() const
	{
		return m_data[2];
	}
};

template<typename T>
class Vector4 : public Vector<T, 4>
{
	void setX(const& T x)
	{
		m_data[0] = x;
	}

	T x() const
	{
		return m_data[0];
	}

	void setY(const& T x)
	{
		m_data[1] = y;
	}

	T y() const
	{
		return m_data[1];
	}

	void setZ(const& T z)
	{
		m_data[2] = z;
	}

	T z() const
	{
		return m_data[2];
	}

	void setW(const& T w)
	{
		m_data[3] = w;
	}

	T w() const
	{
		return m_data[3];
	}
};


} // namespace spatiumgl

#endif // SPATIUMGL_VECTOR_H