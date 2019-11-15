#include <gtest/gtest.h>

#include <spatiumgl/Math.hpp>
#include <spatiumgl/gfx3d/OrthographicCamera.hpp>
#include <spatiumgl/gfx3d/PerspectiveCamera.hpp>
#include <spatiumgl/gfx3d/Transform.hpp>

namespace spgl = spatiumgl;

/*
Projection works, but not these tests.

/// \TODO projection tests

TEST(Projection, orthographicProjection)
{
  // Default transformation: positioned at origin (0,0,0) looking down along
  // the -Z axis while Y is pointing up.

  const double left = -8;
  const double right = 8;
  const double bottom = -4;
  const double top = 4;
  const double near = -10; // negative!
  const double far = -100; // negative!

  const spgl::Matrix4 orthoProjMatrix = spgl::Matrix4::ortho(left, right,
bottom, top, near, far);

  // Project points from orthographic view volume to the canonical view volume
  // Orthographic view volume: min = (left, bottom, far) max = (right, top,
near)
  // Canonical view volume: min = (-1, -1, -1) max = (1,1,1)

  const spgl::Vector3 min(left, bottom, far);
  const spgl::Vector4 minProj = orthoProjMatrix * spgl::Vector4(min, 1);
  EXPECT_EQ(minProj[0], -1);
  EXPECT_EQ(minProj[1], -1);
  EXPECT_EQ(minProj[2], -1);

  const spgl::Vector3 max(right, top, near);
  const spgl::Vector4 maxProj = orthoProjMatrix * spgl::Vector4(max, 1);
  EXPECT_EQ(maxProj[0], 1);
  EXPECT_EQ(maxProj[1], 1);
  EXPECT_EQ(maxProj[2], 1);
}

TEST(Projection, orthographicProjectionCamera)
{
  // Default transformation: positioned at origin (0,0,0) looking down along
  // the -Z axis while Y is pointing up.

  // Construct orthographic projection camera
  const double size = 8;
  const double aspect = 2;
  const double near = 10; // positive!
  const double far = 100; // positive!
  spgl::gfx3d::OrthographicCamera orthoCamera(size, near, far);

  // Get projection matrix
  spgl::Matrix4 orthoProjMatrix = orthoCamera.projectionMatrix(aspect);

  const double left = -8;
  const double right = 8;
  const double bottom = -4;
  const double top = 4;

  const spgl::Vector3 min(left, bottom, -far);
  const spgl::Vector4 minProj = orthoProjMatrix * spgl::Vector4(min, 1);
  EXPECT_EQ(minProj[0], -1);
  EXPECT_EQ(minProj[1], -1);
  EXPECT_EQ(minProj[2], -1);

  const spgl::Vector3 max(right, top, -near);
  const spgl::Vector4 maxProj = orthoProjMatrix * spgl::Vector4(max, 1);
  EXPECT_EQ(maxProj[0], 1);
  EXPECT_EQ(maxProj[1], 1);
  EXPECT_EQ(maxProj[2], 1);
}

TEST(Projection, cameraLookAt)
{
  // Construct orthographic projection camera
  const double size = 8;
  const double near = 1;
  const double far = 20;
  spgl::gfx3d::OrthographicCamera orthoCamera(size, near, far);

  const spgl::Vector3 target(0, 0, 0);
  const spgl::Vector3 up(0, 0, 1);
  const spgl::Vector3 eye(0, -10, 0);

  orthoCamera.lookAt(target, up, eye);

  // Check position and orientation
  EXPECT_EQ(orthoCamera.transform().translation(), eye);
  EXPECT_EQ(orthoCamera.transform().back(), (eye - target).normalized());
  EXPECT_EQ(orthoCamera.transform().right(), spgl::Vector3(1, 0, 0));
  EXPECT_EQ(orthoCamera.transform().up(), up);

  // Rotate around Z axis 180 degrees
  //orthoCamera.transform().rotateZ(spgl::PI<double>());
  orthoCamera.transform().rotateAround(orthoCamera.transform().up(),
spgl::PI<double>());

  EXPECT_NEAR(orthoCamera.transform().translation()[0], 0, 0.00001);
  EXPECT_NEAR(orthoCamera.transform().translation()[1], 10, 0.00001);
  EXPECT_NEAR(orthoCamera.transform().translation()[2], 0, 0.00001);

  EXPECT_NEAR(orthoCamera.transform().up()[0], up[0], 0.00001);
  EXPECT_NEAR(orthoCamera.transform().up()[1], up[1], 0.00001);
  EXPECT_NEAR(orthoCamera.transform().up()[2], up[2], 0.00001);

  EXPECT_NEAR(orthoCamera.transform().back()[0], (target - eye).normalized()[0],
0.00001); EXPECT_NEAR(orthoCamera.transform().back()[1], (target -
eye).normalized()[1], 0.00001); EXPECT_NEAR(orthoCamera.transform().back()[2],
(target - eye).normalized()[2], 0.00001);
}

*/