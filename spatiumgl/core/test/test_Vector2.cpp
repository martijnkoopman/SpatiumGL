#include <gtest/gtest.h>

#include <spatiumgl/Math.hpp>
#include <spatiumgl/Vector.hpp>

TEST(Vector2, constructor)
{
  const spgl::Vector2 v(1, 2);
  EXPECT_EQ(v.x(), 1);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v.y(), 2);
  EXPECT_EQ(v[1], 2);
}

TEST(Vector2, constructorEmpty)
{
  const spgl::Vector2 v;
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 0);
}

TEST(Vector2, constructorInitializerList)
{
  const spgl::Vector2 v1({ 1, 2 });
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);

  const spgl::Vector2 v2 = { 1, 2 };
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
}

TEST(Vector2, cast)
{
  const spgl::Vector2 v1(1, 2);
  const spgl::Vector2f v2 = v1.staticCast<float>();
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
}

TEST(Vector2, accessValue)
{
  const spgl::Vector2 v(1, 2);

  // X
  double x = v[0];
  EXPECT_EQ(x, 1);
  x = v.x();
  EXPECT_EQ(x, 1);

  // Y
  double y = v[1];
  EXPECT_EQ(y, 2);
  y = v.y();
  EXPECT_EQ(y, 2);
}

TEST(Vector2, accessReference)
{
  spgl::Vector2 v(1, 2);

  // X
  v[0] = 3;
  EXPECT_EQ(v[0], 3);
  v.x() = 5;
  EXPECT_EQ(v[0], 5);

  // Y
  v[1] = 4;
  EXPECT_EQ(v[1], 4);
  v.y() = 6;
  EXPECT_EQ(v[1], 6);
}

TEST(Vector2, add)
{
  const spgl::Vector2 v1(1, 2);
  const spgl::Vector2 v2(2, 3);
  const spgl::Vector2 v3 = v1 + v2;
  EXPECT_EQ(v3[0], 3);
  EXPECT_EQ(v3[1], 5);
}

TEST(Vector2, subtract)
{
  const spgl::Vector2 v1(1, 2);
  const spgl::Vector2 v2(2, 3);
  const spgl::Vector2 v3 = v1 - v2;
  EXPECT_EQ(v3[0], -1);
  EXPECT_EQ(v3[1], -1);
}

TEST(Vector2, multiplyScalar)
{
  const spgl::Vector2 v1(1, 2);
  const spgl::Vector2 v2 = v1 * 3;
  EXPECT_EQ(v2[0], 3);
  EXPECT_EQ(v2[1], 6);
}

TEST(Vector2, divideScalar)
{
  const spgl::Vector2 v1(3, 6);
  const spgl::Vector2 v2 = v1 / 3;
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
}

TEST(Vector2, magnitude)
{
  const spgl::Vector2 v1(10, 0);
  EXPECT_EQ(v1.magnitude(), 10);
  const spgl::Vector2 v2(0, 5);
  EXPECT_EQ(v2.magnitude(), 5);
}

TEST(Vector2, normalize)
{
  spgl::Vector2 v(10, 0);
  v.normalize();
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 0);
}

TEST(Vector2, normalized)
{
  const spgl::Vector2 v1(10, 0);
  const spgl::Vector2 v2 = v1.normalized();
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 0);
}

TEST(Vector2, dot)
{
  const spgl::Vector2 v1(1, 0);
  const spgl::Vector2 v2(0, 1);  // perpendicular
  const spgl::Vector2 v3(-1, 0); // parallel
  EXPECT_EQ(v1.dot(v2), 0);
  EXPECT_EQ(v1.dot(v3), -1);
}

TEST(Vector2, angle)
{
  const spgl::Vector2 v1(1, 0);
  const spgl::Vector2 v2(0, 1);
  EXPECT_EQ(v1.angle(v2), 90 * spgl::Deg2Rad<double>());
}

TEST(Vector2, project)
{
  // Example: https://onlinemschool.com/math/library/vector/projection/
  const spgl::Vector2 v1(1, 2);
  const spgl::Vector2 v2(3, 4);
  const spgl::Vector2 result = v2.project(v1);
  const spgl::Vector2 correct(1.32, 1.76);
  EXPECT_NEAR(correct[0], result[0], 0.001);
  EXPECT_NEAR(correct[1], result[1], 0.001);
}

TEST(Vector2, output)
{
  const spgl::Vector2 v(1, 2);
  std::ostringstream ss;
  ss << v;
  EXPECT_EQ(ss.str(), "(1, 2)");
}
