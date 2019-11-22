#include <gtest/gtest.h>

#include <spatiumgl/gfx3d/OrthographicCamera.hpp>

TEST(Camera, constructor)
{
  const double size = 5;
  const double near = 10;
  const double far = 100;
  spgl::gfx3d::OrthographicCamera camera(size, near, far);
  EXPECT_EQ(camera.size(), size);
  EXPECT_EQ(camera.near(), near);
  EXPECT_EQ(camera.far(), far);
}

TEST(Camera, lookAt)
{
  spgl::gfx3d::OrthographicCamera camera(1, 1, 2);

  // Look from above
  const spgl::Vector3 eye1(0, 0, 10);
  const spgl::Vector3 target1(0, 0, 0);
  const spgl::Vector3 up1(0, 1, 0);
  camera.lookAt(target1, up1, eye1);

  // Check vectors
  EXPECT_EQ(camera.transform().right(), spgl::Vector3(1, 0, 0));
  EXPECT_EQ(camera.transform().up(), up1);
  EXPECT_EQ(camera.transform().back(), spgl::Vector3(0, 0, 1));
  EXPECT_EQ(camera.transform().translation(), eye1);

  // Look from the left and upside down
  const spgl::Vector3 eye2(-10, 0, 0);
  const spgl::Vector3 target2(0, 0, 0);
  const spgl::Vector3 up2(0, 0, -1);
  camera.lookAt(target2, up2, eye2);

  // Check vectors
  EXPECT_EQ(camera.transform().right(), spgl::Vector3(0, 1, 0));
  EXPECT_EQ(camera.transform().up(), up2);
  EXPECT_EQ(camera.transform().back(), spgl::Vector3(-1, 0, 0));
  EXPECT_EQ(camera.transform().translation(), eye2);
}

TEST(Camera, orthographicProjection)
{
  const double size = 10;
  const double aspect = 1.5; // 3:2
  const double near = 1;
  const double far = 1000;
  const spgl::gfx3d::OrthographicCamera camera(size, near, far);

  const spgl::Matrix4 matrix = camera.projectionMatrix(aspect);
}