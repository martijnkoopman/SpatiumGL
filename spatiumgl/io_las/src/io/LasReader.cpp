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

#include "spatiumgl/io/LasReader.hpp"

#include "lasreader.hpp"

namespace spatiumgl {
	namespace io {

		class LasReader::Impl
		{
		public:
			Impl(const std::string& path, const bool shiftToOrigin)
				: m_lasreadopener()
				, m_reader(nullptr)
				, m_shiftToOrigin(shiftToOrigin)
			{
				m_lasreadopener.set_file_name(path.c_str());
			}

			~Impl()
			{
				if (m_reader != nullptr)
				{
					close();
				}
			}

			void setPath(const std::string& path)
			{
				m_lasreadopener.set_file_name(path.c_str());
			}

			std::string path() const
			{
				return m_lasreadopener.get_file_name();
			}

			bool isReady() const
			{
				return m_lasreadopener.active();
			}

			bool open()
			{
				close();

				m_reader = m_lasreadopener.open();
				return (m_reader != nullptr);
			}

			bool isOpen() const
			{
				return (m_reader != nullptr);
			}

			void close()
			{
				if (m_reader != nullptr)
				{
					m_reader->close();
					delete m_reader;
					m_reader = nullptr;
				}
			}

			//bool readSinglePoint()
			//{
			//	if (m_reader == nullptr)
			//	{
			//		return false;
			//	}

			//	return m_reader->read_point();
			//}

			//Vector3 lastReadPointPosition()
			//{
			//	if (m_reader == nullptr)
			//	{
			//		return Vector3(0, 0, 0);
			//	}

			//	double x = m_reader->point.get_x();
			//	double y = m_reader->point.get_y();
			//	double z = m_reader->point.get_z();
			//	return Vector3(x, y, z);
			//}

			//Vector3 lastReadPointColor()
			//{
			//	if (m_reader == nullptr)
			//	{
			//		return Vector3(0, 0, 0);
			//	}

			//	double r = static_cast<double>(m_reader->point.get_R()) / 0xFFFF;
			//	double g = static_cast<double>(m_reader->point.get_G()) / 0xFFFF;
			//	double b = static_cast<double>(m_reader->point.get_B()) / 0xFFFF;

			//	return Vector3(r, g, b);
			//}

			gfx3d::PointCloud readAllPoints()
			{
				if (m_reader == nullptr)
				{
					return gfx3d::PointCloud();
				}
				else
				{
					const double x_min = m_reader->get_min_x();
					const double y_min = m_reader->get_min_y();
					const double z_min = m_reader->get_min_z();

					const bool hasColor = hasColors();
					gfx3d::PointCloud pointCloud(m_reader->npoints, hasColor);
					while (m_reader->read_point())
					{
						double x = m_reader->point.get_x();
						double y = m_reader->point.get_y();
						double z = m_reader->point.get_z();

						if (m_shiftToOrigin)
						{
							x -= x_min;
							y -= y_min;
							z -= z_min;
						}

						if (hasColor)
						{
							/// \TODO RGB is always black
							double r = static_cast<double>(m_reader->point.get_R()) / 0xFFFF;
							double g = static_cast<double>(m_reader->point.get_G()) / 0xFFFF;
							double b = static_cast<double>(m_reader->point.get_B()) / 0xFFFF;

							pointCloud.addPoint({ x, y, z }, { r, g, b });
						}
						else
						{
							pointCloud.addPoint({ x, y, z });
						}
					}
					return pointCloud;
				}
			}

			long long int pointCount() const
			{
				if (m_reader == nullptr)
				{
					return 0;
				}

				return m_reader->npoints;
			}

			bool hasColors() const
			{
				if (m_reader == nullptr)
				{
					return false;
				}

				const unsigned char format = m_reader->header.point_data_format;// get_format();
				return (format == 2 || format == 3 || format == 5 || format == 7 || format == 8 || format == 10);
			}

			bool hasNormals() const
			{
				if (m_reader == nullptr)
				{
					return false;
				}

				return false;
			}

      BoundingBox<double> bounds() const
			{
				if (m_reader == nullptr)
				{
          return {};
				}

        return BoundingBox<double>::fromMinMax(
					{ m_reader->get_min_x(), m_reader->get_min_y(), m_reader->get_min_z() },
					{ m_reader->get_max_x(), m_reader->get_max_y(), m_reader->get_max_z() });
			}

		private:
			LASreadOpener m_lasreadopener;
			LASreader* m_reader;
			bool m_shiftToOrigin;
		};

		LasReader::LasReader(const std::string& path, const bool shiftToOrigin)
			: m_pimpl{ std::unique_ptr<Impl>(new Impl(path, shiftToOrigin)) }
		{
		}

		LasReader::~LasReader() = default;

		void LasReader::setPath(const std::string& path)
		{
			m_pimpl->setPath(path);
		}

		std::string LasReader::path() const
		{
			return m_pimpl->path();
		}

		bool LasReader::isReady() const
		{
			return m_pimpl->isReady();
		}

		bool LasReader::open()
		{
			return m_pimpl->open();
		}

		bool LasReader::isOpen()
		{
			return m_pimpl->isOpen();
		}

		gfx3d::PointCloud LasReader::readAllPoints()
		{
			return m_pimpl->readAllPoints();
		}

		void LasReader::close()
		{
			m_pimpl->close();
		}

		//bool LasReader::readSinglePoint()
		//{
		//	return m_pimpl->readSinglePoint();
		//}

		//Vector3 LasReader::lastReadPointPosition()
		//{
		//	return m_pimpl->lastReadPointPosition();
		//}

		//Vector3 LasReader::lastReadPointColor()
		//{
		//	return m_pimpl->lastReadPointColor();
		//}

		long long int LasReader::pointCount() const
		{
			return m_pimpl->pointCount();
		}

		bool LasReader::hasColors() const
		{
			return m_pimpl->hasColors();
		}

		bool LasReader::hasNormals() const
		{
			return m_pimpl->hasNormals();
		}

    BoundingBox<double> LasReader::bounds() const
		{
			return m_pimpl->bounds();
		}
	} // namespace io
} // namespace spatiumgl
