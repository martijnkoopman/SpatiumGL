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

#ifndef SPATIUMGL_RENDEROBJECT_H
#define SPATIUMGL_RENDEROBJECT_H

#include "SceneObject.hpp"
#include "spatiumglexport.h"

#include <array>

namespace spatiumgl {

/// \class RenderObject
/// \brief Scene object that can be rendered.
///
/// A RenderObject has a certain size (bounds).
class SPATIUMGL_EXPORT RenderObject : public SceneObject
{
public:
	RenderObject();

	/// Get the boundaries of the object; axis aligned.
	/// Xmin, Xmax, Ymin, Ymax, Zmin, Zmax
	///
	/// \return Boundaries
	std::array<double, 6> bounds() const;

protected:
	virtual void updateBounds() = 0;

	std::array<double, 6> m_bounds; ///\TODO: use BoundingBox<double, 3> from namespace idx
};

} // namespace spatiumgl

#endif // SPATIUMGL_RENDEROBJECT_H