#include <gtest/gtest.h>

#include <spatiumgl/Bounds.hpp>

TEST(Bounds, defaultConstructors)
{
  spgl::Vector2 center2;
  double radius;
  spgl::Vector2 radii2;
  spgl::Vector2 orientation2;

  spgl::Vector3 center3;
  spgl::Vector3 radii3;
  spgl::Vector3 orientation3;

  const spgl::BoundingCircle circle;
  center2 = circle.center();
  radius = circle.radius();

  const spgl::BoundingEllipse ellipse;
  center2 = ellipse.center();
  radii2 = ellipse.radii();

  const spgl::BoundingSquare square;
  center2 = square.center();
  radius = square.radius();

  const spgl::BoundingRectangle rectangle;
  center2 = rectangle.center();
  radii2 = rectangle.radii();

  const spgl::OrientedBoundingEllipse orientedEllipse;
  center2 = orientedEllipse.center();
  radii2 = orientedEllipse.radii();
  orientation2 = orientedEllipse.orientation();

  const spgl::OrientedBoundingSquare orientedSquare;
  center2 = orientedSquare.center();
  radius = orientedSquare.radius();
  orientation2 = orientedSquare.orientation();

  const spgl::OrientedBoundingRectangle orientedRectangle;
  center2 = orientedRectangle.center();
  radii2 = orientedRectangle.radii();
  orientation2 = orientedRectangle.orientation();

  const spgl::BoundingSphere sphere;
  center3 = sphere.center();
  radius = sphere.radius();

  const spgl::BoundingEllipsoid ellipsoid;
  center3 = ellipsoid.center();
  radii3 = ellipsoid.radii();

  const spgl::BoundingCube cube;
  center3 = cube.center();
  radius = cube.radius();

  const spgl::BoundingBox box;
  center3 = box.center();
  radii3 = box.radii();

  const spgl::OrientedBoundingEllipsoid orientedEllipsoid;
  center3 = orientedEllipsoid.center();
  radii3 = orientedEllipsoid.radii();
  orientation3 = orientedEllipsoid.orientation();

  const spgl::OrientedBoundingCube orientedCube;
  center3 = orientedCube.center();
  radius = orientedCube.radius();
  orientation3 = orientedCube.orientation();

  const spgl::OrientedBoundingBox orientedBox;
  center3 = orientedBox.center();
  radii3 = orientedBox.radii();
  orientation3 = orientedBox.orientation();
}

TEST(BoundingBox, constructor)
{
  const spgl::Vector3 center = { 5, 4, 3 };
  const spgl::Vector3 radii = { 1, 2, 3 };
  const spgl::BoundingBox box(center, radii);
  EXPECT_EQ(box.center(), center);
  EXPECT_EQ(box.radii(), radii);
}

TEST(BoundingBox, fromPoints)
{
  const std::vector<spgl::Vector3> points = { { 1, 4, 7 },
                                              { 2, 5, 8 },
                                              { 3, 6, 9 } };
  const auto box = spgl::BoundingBox::fromPoints(points);
  EXPECT_EQ(box.center(), spgl::Vector3(2, 5, 8));
  EXPECT_EQ(box.radii(), spgl::Vector3(1, 1, 1));
  EXPECT_EQ(box.min(), spgl::Vector3(1, 4, 7));
  EXPECT_EQ(box.max(), spgl::Vector3(3, 6, 9));
}

TEST(BoundingBox, fromMinMax)
{
  const spgl::Vector3 min(2, 3, 4);
  const spgl::Vector3 max(8, 10, 12);
  const auto box = spgl::BoundingBox::fromMinMax(min, max);
  EXPECT_EQ(box.center(), spgl::Vector3(5, 6.5, 8));
  EXPECT_EQ(box.radii(), spgl::Vector3(3, 3.5, 4));
  EXPECT_EQ(box.min(), min);
  EXPECT_EQ(box.max(), max);
}

TEST(BoundingBox, include)
{
  const spgl::Vector3 center(4, 5, 6);
  const spgl::Vector3 radii(1, 1, 1);
  const spgl::Vector3 point1(1, 2, 3);
  const spgl::Vector3 point2(7, 8, 9);
  spgl::BoundingBox box(center, radii);
  box.include(point1);
  box.include(point2);
  EXPECT_EQ(box.min(), point1);
  EXPECT_EQ(box.max(), point2);
}
