#include "spatiumgl/RenderObject.hpp"

namespace spatiumgl {

RenderObject::RenderObject()
	: SceneObject()
	, m_bounds({ 0 })
{}

std::array<double, 6> RenderObject::bounds() const
{
	return m_bounds;
}

} // namespace spatiumgl
