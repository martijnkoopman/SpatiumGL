#include "spatiumgl/SceneObject.hpp"

namespace spatiumgl {

SceneObject::SceneObject()
: m_transform()
{}

Transform & SceneObject::transform()
{
return m_transform;
}

} // namespace spatium
