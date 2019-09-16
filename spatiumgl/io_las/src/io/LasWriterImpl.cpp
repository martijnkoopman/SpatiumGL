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

#include "LasWriterImpl.hpp"

namespace spatiumgl {
	namespace io {
		LasWriterImpl::LasWriterImpl(const std::string& path)
			: m_laswriteopener()
		{
			m_laswriteopener.set_file_name(path.c_str());
		}

		LasWriterImpl::~LasWriterImpl()
		{
		}

		void LasWriterImpl::setPath(const std::string& path)
		{
			m_laswriteopener.set_file_name(path.c_str());
		}

		std::string LasWriterImpl::path() const
		{
			return m_laswriteopener.get_file_name();
		}

		bool LasWriterImpl::isActive() const
		{
			return m_laswriteopener.active();
		}

		bool LasWriterImpl::writePointCloud(const gfx3d::PointCloud& pointCloud)
		{
			const bool hasColors = pointCloud.hasColors();
			//const bool hasNormals = pointCloud.hasNormals();

			// Init header
			LASheader lasheader;
			lasheader.x_scale_factor = 0.01;
			lasheader.y_scale_factor = 0.01;
			lasheader.z_scale_factor = 0.01;
			lasheader.x_offset = 0;
			lasheader.y_offset = 0;
			lasheader.z_offset = 0;
			lasheader.point_data_format = (hasColors ? 2 : 0); // See LAS specification
			lasheader.point_data_record_length = (hasColors ? 26 : 20);

			// Init point 
			LASpoint laspoint;
			laspoint.init(&lasheader, lasheader.point_data_format, lasheader.point_data_record_length, 0);

			// Open laswriter
			std::unique_ptr<LASwriter> laswriter(m_laswriteopener.open(&lasheader));
			if (laswriter == nullptr)
			{
				return false;
			}

			for (size_t i = 0; i < pointCloud.pointCount(); i++)
			{
				// Populate the point
				Vector3 position = pointCloud.position(i);
				laspoint.set_X(static_cast<int>(position.x() * 100));
				laspoint.set_Y(static_cast<int>(position.y() * 100));
				laspoint.set_Z(static_cast<int>(position.z() * 100));
				if (hasColors)
				{
					Vector3 color = pointCloud.color(i);
					laspoint.set_R(static_cast<unsigned short>(color.x() * 0xFFFF));
					laspoint.set_G(static_cast<unsigned short>(color.y() * 0xFFFF));
					laspoint.set_B(static_cast<unsigned short>(color.z() * 0xFFFF));
				}

				// Write the point
				laswriter->write_point(&laspoint);

				// Add it to the inventory
				laswriter->update_inventory(&laspoint);
			}

			// Update the header
			laswriter->update_header(&lasheader, TRUE);

			// close the writer
			I64 total_bytes = laswriter->close();
			// laswriter->p_count;

			return true;
		}
	} // namespace io
} // namespace spatiumgl