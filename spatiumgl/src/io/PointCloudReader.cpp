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
			if (m_reader != nullptr)
			{
				close();
			}
		}

		void setPath(const std::string& path)
		{
			m_lasreadopener.set_file_name(path.c_str());
		}

		bool isActive() const
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

		bool readPoint()
		{
			if (m_reader == nullptr)
			{
				return false;
			}

			return m_reader->read_point();
		}

		Vector3 point()
		{
			if (m_reader == nullptr)
			{
				return Vector3(0,0,0);
			}

			float x = m_reader->point.get_x();
			float y = m_reader->point.get_y();
			float z = m_reader->point.get_z();
			return Vector3(x, y, z);
		}

		long long int pointCount() const
		{
			if (m_reader == nullptr)
			{
				return 0;
			}

			return m_reader->p_count;
		}

		bool hasColor() const
		{
			if (m_reader == nullptr)
			{
				return false;
			}

			int format = m_reader->get_format();
			return (format == 2 || format == 3 || format == 5 || format == 7 || format == 10);
		}

		BoundingBox bounds() const
		{
			if (m_reader == nullptr)
			{
				return BoundingBox();
			}

			return BoundingBox::fromMinMax(
				{ m_reader->get_min_x(), m_reader->get_min_y(), m_reader->get_min_z() }, 
				{ m_reader->get_max_x(), m_reader->get_max_y(), m_reader->get_max_z() });
		}

	private:
		LASreadOpener m_lasreadopener;
		LASreader* m_reader;
	};

	PointCloudReader::PointCloudReader(const std::string& path)
		: m_pimpl{ std::make_unique<impl>(path) }
	{
	}

	PointCloudReader::~PointCloudReader() = default;

	void PointCloudReader::setPath(const std::string& path)
	{
		m_pimpl->setPath(path);
	}

	bool PointCloudReader::isActive() const
	{
		return m_pimpl->isActive();
	}

	bool PointCloudReader::open()
	{
		return m_pimpl->open();
	}

	bool PointCloudReader::isOpen()
	{
		return m_pimpl->isOpen();
	}

	void PointCloudReader::close()
	{
		m_pimpl->close();
	}

	bool PointCloudReader::readPoint()
	{
		return m_pimpl->readPoint();
	}

	Vector3 PointCloudReader::point()
	{
		return m_pimpl->point();
	}

	long long int PointCloudReader::pointCount() const
	{
		return m_pimpl->pointCount();
	}

	bool PointCloudReader::hasColor() const
	{
		return m_pimpl->hasColor();
	}

	BoundingBox PointCloudReader::bounds() const
	{
		return m_pimpl->bounds();
	}
} // namespace spatiumgl