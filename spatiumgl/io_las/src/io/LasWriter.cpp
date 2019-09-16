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

#include "spatiumgl/io/LasWriter.hpp"
#include "LasWriterImpl.hpp"

namespace spatiumgl {
	namespace io {
		LasWriter::LasWriter(const std::string& path)
			: m_pimpl{ std::unique_ptr<LasWriterImpl>(new LasWriterImpl(path)) }
		{
		}

		LasWriter::~LasWriter()
		{
		}

		void LasWriter::setPath(const std::string& path)
		{
			m_pimpl->setPath(path);
		}

		std::string LasWriter::path() const
		{
			return m_pimpl->path();
		}

		bool LasWriter::isReady() const
		{
			return m_pimpl->isActive();
		}

		bool LasWriter::writePointCloud(const gfx3d::PointCloud& pointCloud) const
		{
			return m_pimpl->writePointCloud(pointCloud);
		}
	} // namespace io
} // namespace spatiumgl