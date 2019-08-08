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

#ifndef SPATIUMGL_POINTCLOUDREADER_H
#define SPATIUMGL_POINTCLOUDREADER_H

#include "spatiumgl/spatiumglexport.hpp"
#include "spatiumgl/Vector.hpp"
#include "spatiumgl/Bounds.hpp"

#include <memory> // std::unique_ptr

namespace spatiumgl {

	/// \class PointCloudReader
	/// \brief Read point cloud from file as stream
	class SPATIUMGL_EXPORT PointCloudReader
	{
	public:
		/// Constructor
		///
		/// \param[in] path Path to LAS/LAZ file
		PointCloudReader(const std::string& path = "");

		/// Destructor
		virtual ~PointCloudReader();

		/// Set path to file to read.
		///
		/// \param[in] path Path to LAS/LAZ file
		void setPath(const std::string& path);

		/// Get path to file to read.
		///
		/// \return Path to LAS/LAZ file
		std::string path() const;

		bool isActive() const;

		bool open();

		bool isOpen();
		
		void close();

		bool readPoint();

		Vector3 point();

		long long int pointCount() const;

		bool hasColor() const;

		BoundingBox bounds() const;

	private:
		class impl;     
		std::unique_ptr<impl> m_pimpl;
	};

} // namespace spatiumgl

#endif // SPATIUMGL_POINTCLOUDREADER_H
