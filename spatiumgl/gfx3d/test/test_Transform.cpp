#include <gtest/gtest.h>

#include <spatiumgl/gfx3d/Transform.hpp>
#include <spatiumgl/gfx3d/OrthographicCamera.hpp>
#include <spatiumgl/gfx3d/PointCloud.hpp>
#include <spatiumgl/Math.hpp>

namespace spgl = spatiumgl;

TEST(Transform, defaultConstructor)
{
	const spatiumgl::gfx3d::Transform transform;

	EXPECT_EQ(transform.right(), spatiumgl::Vector3(1, 0, 0));
	EXPECT_EQ(transform.up(), spatiumgl::Vector3(0, 1, 0));
	EXPECT_EQ(transform.back(), spatiumgl::Vector3(0, 0, 1));
	EXPECT_EQ(transform.translation(), spatiumgl::Vector3(0, 0, 0));
}

TEST(Transform, translationMatrix)
{
	// Construct translation matrix
	const double x = 1;
	const double y = 2;
	const double z = 3;
	const spgl::Matrix4 translationMatrix = spgl::Matrix4::translation(x, y, z);
	
	// Translate point
	const spgl::Vector3 point(0, 0, 0);
	const spgl::Vector4 translatedPoint = translationMatrix * spgl::Vector4(point, 1);

	// Check
	EXPECT_EQ(translatedPoint[0], x);
	EXPECT_EQ(translatedPoint[1], y);
	EXPECT_EQ(translatedPoint[2], z);
	EXPECT_EQ(translatedPoint[3], 1);

	// Translate vector (which is nonsense)
	const spgl::Vector3 vector(0, 0, 0);
	const spgl::Vector4 translatedVector = translationMatrix * spgl::Vector4(point, 0);

	// Check
	EXPECT_EQ(translatedVector[0], 0);
	EXPECT_EQ(translatedVector[1], 0);
	EXPECT_EQ(translatedVector[2], 0);
	EXPECT_EQ(translatedVector[3], 0);
}

TEST(Transform, translation)
{
	const double x = 1;
	const double y = 2;
	const double z = 3;
	const spatiumgl::Vector3 position(x, y, z);

	spatiumgl::gfx3d::Transform transform;
	transform.setTranslation(position);
	EXPECT_EQ(transform.translation(), position);

	EXPECT_EQ(transform.matrix()[3][0], x);
	EXPECT_EQ(transform.matrix()[3][1], y);
	EXPECT_EQ(transform.matrix()[3][2], z);

	EXPECT_EQ(transform.matrix().data()[12], x);
	EXPECT_EQ(transform.matrix().data()[13], y);
	EXPECT_EQ(transform.matrix().data()[14], z);

	// Diagonal identity
	EXPECT_EQ(transform.matrix()[0][0], 1);
	EXPECT_EQ(transform.matrix()[1][1], 1);
	EXPECT_EQ(transform.matrix()[2][2], 1);
	EXPECT_EQ(transform.matrix()[3][3], 1);

	EXPECT_EQ(transform.matrix().data()[0], 1);
	EXPECT_EQ(transform.matrix().data()[5], 1);
	EXPECT_EQ(transform.matrix().data()[10], 1);
	EXPECT_EQ(transform.matrix().data()[15], 1);
}

TEST(Transform, translate)
{
	const double x = 1;
	const double y = 2;
	const double z = 3;

	// Create translation transform
	const spgl::Vector3 translation(x, y, z);
	spgl::gfx3d::Transform transform;
	transform.translate(translation);

	// Object to world point via translation
	const spgl::Vector3 worldPoint = transform.objectPointToWorldPoint(spgl::Vector3(0,0,0));

	// Check point
	EXPECT_EQ(translation, worldPoint);
}

TEST(Transform, rotationY)
{
	const spgl::Vector3 point(1, 0, 0);
	const spgl::Vector3 correctRotatedPoint(-1, 0, 0);

	// Rotate directly via matrix
	const spgl::Matrix4 rotationY = spgl::Matrix4::rotationZ(spgl::PI<double>());
	const spgl::Vector4 rotatedPoint1 = rotationY * spgl::Vector4(point, 1);

	// Check rotation
	EXPECT_NEAR(rotatedPoint1[0], correctRotatedPoint[0], 0.00001);
	EXPECT_NEAR(rotatedPoint1[1], correctRotatedPoint[1], 0.00001);
	EXPECT_NEAR(rotatedPoint1[2], correctRotatedPoint[2], 0.00001);
	EXPECT_NEAR(rotatedPoint1[3], 1, 0.00001);

	// Create empty transform
	spgl::gfx3d::Transform transform;
	const spgl::Vector3 worldPoint = transform.objectPointToWorldPoint(point);
	
	// Check point
	EXPECT_EQ(point, worldPoint);

	// Rotate via transform
	transform.rotateY(spgl::PI<double>());
	const spgl::Vector3 rotatedPoint2 = transform.objectPointToWorldPoint(point);

	EXPECT_NEAR(rotatedPoint2[0], -1, 0.00001);
	EXPECT_NEAR(rotatedPoint2[1], 0, 0.00001);
	EXPECT_NEAR(rotatedPoint2[2], 0, 0.00001);
}

TEST(Transform, cameraLookAt)
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
	orthoCamera.transform().rotateAround(orthoCamera.transform().up(), spgl::PI<double>());

	EXPECT_NEAR(orthoCamera.transform().translation()[0], 0, 0.00001);
	EXPECT_NEAR(orthoCamera.transform().translation()[1], 10, 0.00001);
	EXPECT_NEAR(orthoCamera.transform().translation()[2], 0, 0.00001);

	EXPECT_NEAR(orthoCamera.transform().up()[0], up[0], 0.00001);
	EXPECT_NEAR(orthoCamera.transform().up()[1], up[1], 0.00001);
	EXPECT_NEAR(orthoCamera.transform().up()[2], up[2], 0.00001);

	EXPECT_NEAR(orthoCamera.transform().back()[0], (target - eye).normalized()[0], 0.00001);
	EXPECT_NEAR(orthoCamera.transform().back()[1], (target - eye).normalized()[1], 0.00001);
	EXPECT_NEAR(orthoCamera.transform().back()[2], (target - eye).normalized()[2], 0.00001);
}
