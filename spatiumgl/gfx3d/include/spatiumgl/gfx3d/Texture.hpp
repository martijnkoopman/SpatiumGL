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

#ifndef SPATIUMGL_TEXTURE_H
#define SPATIUMGL_TEXTURE_H

#include "spatiumglexport.hpp"

namespace spatiumgl {

/// \class Mesh
/// \brief Triangluar mesh
///
/// ...
class SPATIUMGL_EXPORT Texture
{
public:

	//enum InternalFormat
	//{
	//	DEPTH_COMPONENT,
	//	DEPTH_STENCIL,
	//	RED,	// 1 channel
	//	RG,		// 2
	//	RGB,	// 3
	//	RGBA	// 4
	//};

	enum PixelFormat
	{
		RED,	// 1 channel
		RG,		// 2
		RGB,	// 3
		RGBA,	// 4
		STENCIL_INDEX, 
		DEPTH_COMPONENT, 
		DEPTH_STENCIL
	};

	enum PixelType
	{
		UNSIGNED_BYTE,
		BYTE,
		UNSIGNED_SHORT,
		SHORT,
		UNSIGNED_INT,
		INT,
		FLOAT
	};

	/// Constructor
	///
	/// \param[in] width Width
	/// \param[in] height Height
	/// \param[in] pixelFormat Pixel format
	/// \param[in] pixelType Pixel type
	/// \param[in] generateMipmap Generate mipmap (default = false)
	Texture(int width, int height, PixelFormat pixelFormat, PixelType pixelType, bool generateMipmap=false)
		: m_width(width < 0 ? 0 < width)
		, m_height(height < 0 ? 0 < height)
		, m_pixelFormat(pixelFormat)
		, m_pixelType(pixelType)
	{
		int byteCount = channelSize(m_pixelType) * channelCount(m_pixelFormat) * m_width * m_height;
		m_data = new unsigned char[byteCount];
	}

	~Texture()
	{
		delete[] m_data;
	}

	void bind() const override
	{
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	void map() const override
	{

		glTexImage2D(GL_TEXTURE_2D, (0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	static int channelCount(PixelFormat pixelFormat)
	{
		switch (pixelFormat)
		{
		case RED:
			return 1;
		case RG:
			return 2;
		case RGB:
			return 3;
		case RGBA:
			return 4;
		case STENCIL_INDEX:
			return 1;
		case DEPTH_COMPONENT:
			return 1;
		case DEPTH_STENCIL:
			return 2;
		}
	}

	static int channelSize(PixelType pixelType)
	{
		switch (pixelType)
		{
		case UNSIGNED_BYTE:
			return sizeof(unsigned char);
		case BYTE:
			return sizeof(char);
		case UNSIGNED_SHORT:
			return sizeof(unsigned short);
		case SHORT:
			return sizeof(short);
		case UNSIGNED_INT:
			return sizeof(unsigned int);
		case INT:
			return sizeof(int);
		case FLOAT:
			return sizeof(float);
		default:
			return 0;
		}
	}

protected:
	//InternalFormat m_internalFormat;
	int m_width;
	int m_height;
	PixelFormat m_pixelFormat;
	PixelType m_pixelType;
	unsigned char m_data[];

	// Inernal
	unsigned int m_textureId;
};

} // namespace spatiumgl

#endif // SPATIUMGL_TEXTURE_H