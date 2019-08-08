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

#include <cstring> // strncpy memset

#include <glm/vec3.hpp> 

#include <memory> // std::unique_ptr
#include <string>
#include <array>

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

		std::array<double, 6> bounds() const;

		bool open();

		bool isOpen();
		
		void close();

		bool readPoint();
		glm::vec3 point();

		Vector3 test() const
		{
			return Vector3(1, 2, 3);
		}

	private:
		class impl;     
		std::unique_ptr<impl> pimpl;
	};

} // namespace spatiumgl

#endif // SPATIUMGL_POINTCLOUDREADER_H
