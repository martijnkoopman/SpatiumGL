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

#include "spatiumgl/io/PointCloudReader.hpp"

#include "lasreader.hpp"

namespace spatiumgl {

	class PointCloudReader::impl
	{
	public:
		impl(const std::string& path)
			: m_lasreadopener()
			, m_reader(nullptr)
		{

		}

		~impl()
		{
			if (m_reader)
			{
				close();
			}
		}

		void setPath(const std::string& path)
		{
			m_lasreadopener.set_file_name(path.c_str());
		}

		std::array<double, 6> bounds() const
		{
			if (m_reader == nullptr)
			{
				return { 0, 0, 0, 0, 0, 0 };
			}

			return { m_reader->header.min_x,
				   m_reader->header.min_y,
				   m_reader->header.min_z,
				   m_reader->header.max_x,
				   m_reader->header.max_y,
				   m_reader->header.max_z
			};
		}

		bool open()
		{
			close();

			m_reader = m_lasreadopener.open();
			return (m_reader != nullptr);
		}

		//
		//	bool PointCloudReader::isOpen()
		//	{
		//		//
		//	}
		//

		void close()
		{
			if (m_reader)
			{
				m_reader->close();
				delete m_reader;
				m_reader = nullptr;
			}
		}

		bool readPoint()
		{
			if (m_reader == nullptr)
			{
				return false;
			}

			return m_reader->read_point();
		}

		glm::vec3 point()
		{
			if (m_reader == nullptr)
			{
				return glm::vec3(0, 0, 0);
			}

			float x = m_reader->point.get_x();
			float y = m_reader->point.get_y();
			float z = m_reader->point.get_z();
			return glm::vec3(x, y, z);
		}

	private:
		LASreadOpener m_lasreadopener;
		LASreader* m_reader;
	};

	PointCloudReader::PointCloudReader(const std::string& path)
		: pimpl{ std::make_unique<impl>(path) }
	{
	}

	PointCloudReader::~PointCloudReader() = default;

	void PointCloudReader::setPath(const std::string& path)
	{
		pimpl->setPath(path);
	}

	std::array<double, 6> PointCloudReader::bounds() const
	{
		return pimpl->bounds();
	}

	bool PointCloudReader::open()
	{
		return pimpl->open();
	}

	//
	//	bool PointCloudReader::isOpen()
	//	{
	//		//
	//	}
	//

	void PointCloudReader::close()
	{
		pimpl->close();
	}

	bool PointCloudReader::readPoint()
	{
		return pimpl->readPoint();
	}

	glm::vec3 PointCloudReader::point()
	{
		return pimpl->point();
	}
} // namespace spatiumgl