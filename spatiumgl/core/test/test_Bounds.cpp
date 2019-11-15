#include <gtest/gtest.h>

#include <spatiumgl/Bounds.hpp>

TEST(Bounds, defaultConstructors)
{
	spatiumgl::Vector2 center2;
  double radius;
	spatiumgl::Vector2 radii2;
	spatiumgl::Vector2 orientation2;

	spatiumgl::Vector3 center3;
	spatiumgl::Vector3 radii3;
	spatiumgl::Vector3 orientation3;

  const spatiumgl::BoundingCircle<double> circle;
	center2 = circle.center(); 
	radius = circle.radius();

  const spatiumgl::BoundingEllipse<double> ellipse;
	center2 = ellipse.center();
	radii2 = ellipse.radii();

  const spatiumgl::BoundingSquare<double> square;
	center2 = square.center();
	radius = square.radius();

  const spatiumgl::BoundingRectangle<double> rectangle;
	center2 = rectangle.center();
	radii2 = rectangle.radii();

  const spatiumgl::OrientedBoundingEllipse<double> orientedEllipse;
	center2 = orientedEllipse.center();
	radii2 = orientedEllipse.radii();
	orientation2 = orientedEllipse.orientation();

  const spatiumgl::OrientedBoundingSquare<double> orientedSquare;
	center2 = orientedSquare.center();
	radius = orientedSquare.radius();
	orientation2 = orientedSquare.orientation();

  const spatiumgl::OrientedBoundingRectangle<double> orientedRectangle;
	center2 = orientedRectangle.center();
	radii2 = orientedRectangle.radii();
	orientation2 = orientedRectangle.orientation();

  const spatiumgl::BoundingSphere<double> sphere;
	center3 = sphere.center();
	radius = sphere.radius();

  const spatiumgl::BoundingEllipsoid<double> ellipsoid;
	center3 = ellipsoid.center();
	radii3 = ellipsoid.radii();

  const spatiumgl::BoundingCube<double> cube;
	center3 = cube.center();
	radius = cube.radius();

  const spatiumgl::BoundingBox<double> box;
	center3 = box.center();
	radii3 = box.radii();

  const spatiumgl::OrientedBoundingEllipsoid<double> orientedEllipsoid;
	center3 = orientedEllipsoid.center();
	radii3 = orientedEllipsoid.radii();
	orientation3 = orientedEllipsoid.orientation();

  const spatiumgl::OrientedBoundingCube<double> orientedCube;
	center3 = orientedCube.center();
	radius = orientedCube.radius();
	orientation3 = orientedCube.orientation();

  const spatiumgl::OrientedBoundingBox<double> orientedBox;
	center3 = orientedBox.center();
	radii3 = orientedBox.radii();
	orientation3 = orientedBox.orientation();
}

TEST(BoundingBox, constructor)
{
	const spatiumgl::Vector3 center = { 5, 4, 3 };
	const spatiumgl::Vector3 radii = { 1, 2, 3 };
  const spatiumgl::BoundingBox<double> box(center, radii);
	EXPECT_EQ(box.center(), center);
	EXPECT_EQ(box.radii(), radii);
}

TEST(BoundingBox, fromPoints)
{
	const std::vector<spatiumgl::Vector3> points = { {1,4,7}, {2,5,8}, {3,6,9} };
  const auto box = spatiumgl::BoundingBox<double>::fromPoints(points);
	EXPECT_EQ(box.center(), spatiumgl::Vector3(2,5,8));
	EXPECT_EQ(box.radii(), spatiumgl::Vector3(1, 1, 1));
	EXPECT_EQ(box.min(), spatiumgl::Vector3(1, 4, 7));
	EXPECT_EQ(box.max(), spatiumgl::Vector3(3, 6, 9));
}

TEST(BoundingBox, fromMinMax)
{
	const spatiumgl::Vector3 min(2, 3, 4);
	const spatiumgl::Vector3 max(8, 10, 12);
  const auto box = spatiumgl::BoundingBox<double>::fromMinMax(min, max);
	EXPECT_EQ(box.center(), spatiumgl::Vector3(5,6.5,8));
	EXPECT_EQ(box.radii(), spatiumgl::Vector3(3,3.5,4));
	EXPECT_EQ(box.min(), min);
	EXPECT_EQ(box.max(), max);
}

TEST(BoundingBox, include)
{
	const spatiumgl::Vector3 center(4, 5, 6);
	const spatiumgl::Vector3 radii(1, 1, 1);
	const spatiumgl::Vector3 point1(1, 2, 3);
	const spatiumgl::Vector3 point2(7, 8, 9);
  spatiumgl::BoundingBox<double> box(center, radii);
	box.include(point1);
	box.include(point2);
	EXPECT_EQ(box.min(), point1);
	EXPECT_EQ(box.max(), point2);
}
