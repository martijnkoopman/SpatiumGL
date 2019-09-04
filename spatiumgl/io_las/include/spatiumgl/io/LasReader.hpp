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

#ifndef SPATIUMGL_IO_LAS_LASREADER_H
#define SPATIUMGL_IO_LAS_LASREADER_H

#include "spatiumglexport.hpp"
#include "spatiumgl/gfx3d/PointCloud.hpp"

#include <memory> // std::unique_ptr

namespace spatiumgl {
	namespace io {

		/// \class PointCloudReader
		/// \brief Read point cloud from file as stream
		class SPATIUMGL_EXPORT LasReader
		{
		public:
			/// Constructor
			///
			/// \param[in] path Path to LAS/LAZ file
			LasReader(const std::string& path = "");

			/// Destructor
			virtual ~LasReader();

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

			gfx3d::PointCloud readAll();

			bool readPoint();

			Vector3 point();

			long long int pointCount() const;

			bool hasColor() const;

			/// Return bounds of dataset
			BoundingBox<SPATIUMGL_PRECISION> bounds() const;

		private:
			class impl;
			std::unique_ptr<impl> m_pimpl;
		};

	} // namespace io
} // namespace spatiumgl

#endif // SPATIUMGL_IO_LAS_LASREADER_H
