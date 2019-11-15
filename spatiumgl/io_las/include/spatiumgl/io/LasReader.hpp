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
		/// \brief Read point cloud from LAS/LAZ file.
		class SPATIUMGL_EXPORT LasReader
		{
		public:
			/// Constructor
			///
			/// \param[in] path Path to LAS/LAZ file
      LasReader(const std::string& path = "", bool shiftToOrigin = false);

			/// Destructor
			virtual ~LasReader(); // Must be virtual for PIMPL pattern

			/// Set path to file to read.
			///
			/// \param[in] path Path to LAS/LAZ file
			void setPath(const std::string& path);

			/// Get path to file to read.
			///
			/// \return Path to LAS/LAZ file
			std::string path() const;

			/// ???
			bool isReady() const;

			/// Open file input stream.
			///
			/// This function may fail for various reasons: file doesn't 
			/// exist, no permission to read, etc. 
			///
			/// \return True on success, false otherwise
			bool open();

			/// Check whether the file stream is open.
			///
			/// \return True if open, false otherwise
			bool isOpen();

			/// Close the file input stream.
			void close();

			/// Read all points from file into a point cloud.
			///
			/// \return PointCloud
			gfx3d::PointCloud readAllPoints();

			/// Read single point from input file stream.
			///
			/// \return True on read, false on end-of-file
			bool readSinglePoint();

			/// Get the last read point position.
			///
			/// The point should first be read with readSinglePoint()
			///
			/// \return Last read point position
			/// \sa readSinglePoint()
			Vector3 lastReadPointPosition();

			/// Get the last read point color.
			///
			/// The point should first be read with readSinglePoint()
			///
			/// \return Last read point color
			/// \sa readSinglePoint()
			Vector3 lastReadPointColor();

			/// Get the total point count according to the file header.
			///
			/// \return Point count
			long long int pointCount() const;

			/// Indicator if the points have normals, according to the file header.
			///
			/// \return True if points have colors, false otherwise
			bool hasColors() const;

			/// Indicator if points have normals, according to the file header.
			///
			/// \return True if points have normals, false otherwise
			bool hasNormals() const;

			/// Gte the boundaries of all points combined, according to the file header.
			///
			/// \return Boundaries
      BoundingBox<double> bounds() const;

		private:
			class Impl;
			std::unique_ptr<Impl> m_pimpl;
		};

	} // namespace io
} // namespace spatiumgl

#endif // SPATIUMGL_IO_LAS_LASREADER_H
