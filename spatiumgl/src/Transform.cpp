#include "spatiumgl/Transform.hpp"

#include <glm/matrix.hpp> // inverse
#include <glm/gtc/matrix_access.hpp>

namespace spatiumgl {

Transform::Transform()
    : m_matrix() // identity matrix
  {
	  m_matrix[0][0] = 1.0f;
	  m_matrix[1][1] = 1.0f;
	  m_matrix[2][2] = 1.0f;
	  m_matrix[3][3] = 1.0f;
  }

  glm::vec3 Transform::right() const
  {
	return glm::column(m_matrix, 0);
  }

  glm::vec3 Transform::up() const
  {
	  return glm::column(m_matrix, 1);
  }

  glm::vec3 Transform::back() const
  {
	return glm::column(m_matrix, 2);
  }

  glm::vec3 Transform::position() const
  {
	return glm::column(m_matrix, 3);
  }

  void Transform::setPosition(const glm::vec3 &position)
  {
	  m_matrix = glm::column(m_matrix, 3, glm::vec4(position, 1.0f));
  }

  /*
  /// Translate in world space
  ///
  /// \param[in] xyz Translation on X, Y and Z axis
  void translate(const geom3d::Vector3 &xyz)
  {
    m_matrix(0,3) = m_matrix(0,3) + xyz.x();
    m_matrix(1,3) = m_matrix(1,3) + xyz.y();
    m_matrix(2,3) = m_matrix(2,3) + xyz.z();
  }

  /// Get the scale
  ///
  /// \return Scale on x, y and z axis
  geom3d::Vector3 scale() const
  {
    const geom3d::Matrix4x4 &M = m_matrix;
    double x = geom3d::Vector3(M(0,0), M(1,0), M(2,0)).length(); // 1st column
    double y = geom3d::Vector3(M(0,1), M(1,1), M(2,1)).length(); // 2nd column
    double z = geom3d::Vector3(M(0,2), M(1,2), M(2,2)).length(); // 3rd column
    return geom3d::Vector3(x,y,z);
  }

  /// Rotate (relative to self/object space)
  ///
  /// \param[in] euler Degrees around x, y and z axis
  void rotate(const geom3d::Vector3 &euler)
  {
    ///\todo This doesn't work... Use TRS?
    m_matrix = m_matrix * geom3d::Matrix4x4::rotation(euler.x(), euler.y(), euler.z());
  }

  /// Rotate around axis (relative to self/object space)
  ///
  /// \param[in] axis Axis vector
  /// \param[in] angle Angle in radians
  void rotateAround(const geom3d::Vector3 &axis, double angle)
  {
    m_matrix = geom3d::Matrix4x4::rotationAround(axis, angle) * m_matrix;
  }

  /// Set the rotation in world space
  ///
  /// \param[in] euler Rotation in euler angles
  void setRotation(const geom3d::Vector3 &euler)
  {
    // Extract scale and translation from current matrix
    geom3d::Vector3 s = scale();
    geom3d::Point3 t = position();

    // Create translation, rotation and scale matrix
    geom3d::Matrix4x4 T = geom3d::Matrix4x4::translation(t.x(), t.y(), t.z());
    geom3d::Matrix4x4 R = geom3d::Matrix4x4::rotation(euler.x(), euler.y(), euler.z());
    geom3d::Matrix4x4 S = geom3d::Matrix4x4::scaling(s.x(), s.y(), s.z());

    // Constrcut matrix (scale first, then rotate, then translate)
    m_matrix = T * R * S;
  }

  /// Get the rotation in world space
  ///
  /// \return Rotation in euler angles
  geom3d::Vector3 rotation() const
  {
    ///\todo Check if should each column should be scaled first?

    // Extract euler angles from matrix
    double x, y, z;
    const geom3d::Matrix4x4 &M = m_matrix;
    if (M(2,0) != 1 && M(2,0) != -1) ///\todo Unsafe compare
    {
      y = -asin(M(2,0));
      x = atan2(M(2,1) / cos(y), M(2,2) / cos(y));
      z = atan2(M(1,0) / cos(y), M(0,0) / cos(y));

      // There is a second solution:
      //theta = spatium::PI - theta;
      //psi = atan2( M(2,1) / cos(theta), M(2,2) / cos(theta));
      //phi = atan2( M(1,0) / cos(theta), M(0,0) / cos(theta));
    }
    else
    {
      // There is an infinit amount of solutions
      // Z can have an arbitrary value
      z = 0;
      if (M(2,0) == -1) ///\todo Unsafe compare
      {
        y = spatium::PI / 2;
        x = z + atan2(M(0,1), M(0,2));
      }
      else
      {
        y = -spatium::PI / 2;
        x = -z + atan2(-M(0,1), -M(0,2));
      }
    }

    return geom3d::Vector3(x,y,z);
  }
  */

  void Transform::setMatrix(const glm::mat4 &matrix)
  {
    m_matrix = matrix;
  }

  glm::mat4 Transform::matrix() const
  {
    return m_matrix;
  }

  glm::vec3 Transform::objectPointToWorldPoint(const glm::vec3 &point) const
  {
    return m_matrix * glm::vec4(point, 1.0f);
  }

  glm::vec3 Transform::worldPointToObjectPoint(const glm::vec3 &point) const
  {
    return glm::inverse(m_matrix) * glm::vec4(point, 1.0f);
  }

} // namespace spatiumgl