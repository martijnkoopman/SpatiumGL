#include <gtest/gtest.h>

#include <spatiumgl/Vector.hpp>

TEST(Vector, constructor)
{
  spgl::Vector<double, 3> vec1; // 0 0 0
  EXPECT_EQ(vec1[0], 0);
  EXPECT_EQ(vec1[1], 0);
  EXPECT_EQ(vec1[2], 0);

  spgl::Vector<double, 3> vec2(1); // 1 1 1
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 1);
  EXPECT_EQ(vec2[2], 1);

  spgl::Vector<double, 3> vec3{1}; // 1 1 1
  EXPECT_EQ(vec3[0], 1);
  EXPECT_EQ(vec3[1], 1);
  EXPECT_EQ(vec3[2], 1);

  spgl::Vector<double, 3> vec5(1, 2, 3);
  EXPECT_EQ(vec5[0], 1);
  EXPECT_EQ(vec5[1], 2);
  EXPECT_EQ(vec5[2], 3);

  spgl::Vector<double, 3> vec6{ 1, 2, 3 };
  EXPECT_EQ(vec6[0], 1);
  EXPECT_EQ(vec6[1], 2);
  EXPECT_EQ(vec6[2], 3);

  spgl::Vector<double, 3> vec7({ 1, 2, 3 });
  EXPECT_EQ(vec7[0], 1);
  EXPECT_EQ(vec7[1], 2);
  EXPECT_EQ(vec7[2], 3);
}

TEST(Vector, assignment)
{
  spgl::Vector<double, 3> vec1 = {};
  EXPECT_EQ(vec1[0], 0);
  EXPECT_EQ(vec1[1], 0);
  EXPECT_EQ(vec1[2], 0);

  spgl::Vector<double, 3> vec2 = { 1 };
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 1);
  EXPECT_EQ(vec2[2], 1);

  spgl::Vector<double, 3> vec3 = { 1, 2, 3 };
  EXPECT_EQ(vec3[0], 1);
  EXPECT_EQ(vec3[1], 2);
  EXPECT_EQ(vec3[2], 3);
}

TEST(Vector, accessElements)
{
  spgl::Vector<double, 1> vec1{ 1 };
  double& x1 = vec1.x();
  const spgl::Vector<double, 1> vec1_const{ 1 };
  const double& x1_const = vec1_const.x();

  EXPECT_EQ(x1, 1);
  EXPECT_EQ(x1_const, 1);

  spgl::Vector<double, 2> vec2{ 1, 2 };
  double& x2 = vec2.x();
  double& y2 = vec2.y();
  const spgl::Vector<double, 2> vec2_const{ 1, 2 };
  const double& x2_const = vec2_const.x();
  const double& y2_const = vec2_const.y();

  EXPECT_EQ(x2, 1);
  EXPECT_EQ(y2, 2);
  EXPECT_EQ(x2_const, 1);
  EXPECT_EQ(y2_const, 2);

  spgl::Vector<double, 3> vec3{ 1, 2, 3 };
  double& x3 = vec3.x();
  double& y3 = vec3.y();
  double& z3 = vec3.z();
  const spgl::Vector<double, 3> vec3_const{ 1, 2, 3 };
  const double& x3_const = vec3_const.x();
  const double& y3_const = vec3_const.y();
  const double& z3_const = vec3_const.z();

  EXPECT_EQ(x3, 1);
  EXPECT_EQ(y3, 2);
  EXPECT_EQ(z3, 3);
  EXPECT_EQ(x3_const, 1);
  EXPECT_EQ(y3_const, 2);
  EXPECT_EQ(z3_const, 3);

  spgl::Vector<double, 4> vec4{ 1, 2, 3, 4 };
  double& x4 = vec4.x();
  double& y4 = vec4.y();
  double& z4 = vec4.z();
  double& w4 = vec4.w();
  const spgl::Vector<double, 4> vec4_const{ 1, 2, 3, 4 };
  const double& x4_const = vec4_const.x();
  const double& y4_const = vec4_const.y();
  const double& z4_const = vec4_const.z();
  const double& w4_const = vec4_const.w();

  EXPECT_EQ(x4, 1);
  EXPECT_EQ(y4, 2);
  EXPECT_EQ(z4, 3);
  EXPECT_EQ(w4, 4);
  EXPECT_EQ(x4_const, 1);
  EXPECT_EQ(y4_const, 2);
  EXPECT_EQ(z4_const, 3);
  EXPECT_EQ(w4_const, 4);
}
