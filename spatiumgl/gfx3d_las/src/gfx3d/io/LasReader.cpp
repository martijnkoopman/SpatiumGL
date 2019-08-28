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

#include "spatiumgl/gfx3d/io/LasReader.hpp"

#include "lasreader.hpp"

namespace spatiumgl {

	class LasReader::impl
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

		std::string path() const
		{
			return m_lasreadopener.get_file_name();
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

			return m_reader->npoints;
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

	LasReader::LasReader(const std::string& path)
		: m_pimpl{ std::make_unique<impl>(path) }
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

	bool LasReader::isActive() const
	{
		return m_pimpl->isActive();
	}

	bool LasReader::open()
	{
		return m_pimpl->open();
	}

	bool LasReader::isOpen()
	{
		return m_pimpl->isOpen();
	}

	void LasReader::close()
	{
		m_pimpl->close();
	}

	bool LasReader::readPoint()
	{
		return m_pimpl->readPoint();
	}

	Vector3 LasReader::point()
	{
		return m_pimpl->point();
	}

	long long int LasReader::pointCount() const
	{
		return m_pimpl->pointCount();
	}

	bool LasReader::hasColor() const
	{
		return m_pimpl->hasColor();
	}

	BoundingBox LasReader::bounds() const
	{
		return m_pimpl->bounds();
	}
} // namespace spatiumgl