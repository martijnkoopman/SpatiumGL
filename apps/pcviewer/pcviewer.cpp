#include <spatiumgl/Vector.hpp>
#include <spatiumgl/Matrix.hpp>
#include <spatiumgl/Math.hpp>
#include <spatiumgl/gfx3d/Camera.hpp>
#include <spatiumgl/gfx3d/PointCloud.hpp>
#include <spatiumgl/io/LasReader.hpp>
#include <spatiumgl/gfx3d/OGLPointCloudRenderer.hpp>
#include <spatiumgl/gfx3d/GlfwRenderWindow.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
	std::string path;
	// Get path from command line arguments
	if (argc != 2)
	{
		std::cerr << "usage: pcviewer file.las" << std::endl;
		//return 1;
		path = "C:\\Users\\Martijn\\Downloads\\autzen_sub.laz";
	}
	else {
		path = argv[1];
	}

	spatiumgl::io::LasReader reader(path);
	if (!reader.isActive())
	{
		std::cerr << "Invalid input file: " << path << std::endl;
		return 1;
	}

	if (!reader.open())
	{
		std::cerr << "Unable to open file: " << path << std::endl;
		return 1;
	}

	spatiumgl::Vector3 min = reader.bounds().min();
	std::vector<spatiumgl::Vector3> positions;
	while (reader.readPoint())
	{
		spatiumgl::Vector3 pt = reader.point() - min;
		positions.push_back(pt);
	}
	spatiumgl::gfx3d::PointCloud pointcloud(positions);

	// Optional: request OpenGL context version with glfwWindowHint()

	spatiumgl::gfx3d::GlfwRenderWindow renderWindow(true);
	if (!renderWindow.init())
	{
		std::cerr << "Failed to initialize GLFW." << std::endl;
		return 1;
	}

	// Create window with OpenGL context
	if (!renderWindow.createWindow(640, 480))
	{
		std::cerr << "Failed to create window or OpenGL context." << std::endl;

		// Release resources of GLFW
		renderWindow.terminate();
		return 1;
	}

	// BEGIN: OpenGL rendering stuff...
	
	spatiumgl::gfx3d::Camera camera(45.0 * spatiumgl::Deg2Rad<double>(), 1.0, 10000.0);
	camera.lookAt(spatiumgl::Vector3(0, -10, 0), spatiumgl::Vector3(0, 0, 0), spatiumgl::Vector3(0,0,1));
	//std::cout << glm::to_string(camera->transform().matrix()) << std::endl;
	//std::cout << "Camera pos: " << camera->transform().position().x << " " << camera->transform().position().y << " " << camera->transform().position().z << std::endl;
	//std::cout << "Camera up: " << camera->transform().up().x << " " << camera->transform().up().y << " " << camera->transform().up().z << std::endl;
	//std::cout << "Camera right: " << camera->transform().right().x << " " << camera->transform().right().y << " " << camera->transform().right().z << std::endl;
	//std::cout << "Camera back: " << camera->transform().back().x << " " << camera->transform().back().y << " " << camera->transform().back().z << std::endl;
	renderWindow.setCamera(&camera);

	// Create point cloud
	//std::vector<glm::vec3> positions = { {0.0f,  0.0f, 1.0f },
	//									{ 1.0f,  0.0f, -1.0f },
	//									{ -1.0f, 0.0f, -1.0f } };
	//std::vector<glm::vec3> colors = {
	//	{ 1.0f, 0.0f, 0.0f },
	//	{ 0.0f, 1.0f, 0.0f },
	//	{ 0.0f, 0.0f, 1.0f }
	//};
	// Create point cloud renderer
	spatiumgl::gfx3d::OGLPointCloudRenderer renderer(&pointcloud);
	if (!renderer.isValid())
	{
		// Exit
		renderWindow.terminate();
		return 1;
	}

	renderWindow.setRenderer(&renderer);
	renderWindow.show();

	renderWindow.destroyWindow();
	// Release resources
	renderWindow.terminate();

	return 0;
}
