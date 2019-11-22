#include <spatiumgl/Math.hpp>
#include <spatiumgl/gfx3d/GlfwRenderWindow.hpp>
#include <spatiumgl/gfx3d/OGLPointCloudRenderer.hpp>
#include <spatiumgl/gfx3d/PerspectiveCamera.hpp>
#include <spatiumgl/gfx3d/PivotInteractor.hpp>
#include <spatiumgl/gfx3d/PointCloud.hpp>
#include <spatiumgl/gfx3d/PointCloudObject.hpp>
#include <spatiumgl/io/LasReadTask.hpp>

#include <iostream>

namespace spgl = spatiumgl;

int
main(int argc, char* argv[])
{
  // Get path from command line arguments
  std::string path;
  if (argc != 2) {
    std::cerr << "usage: lasviewer <file.las/laz>" << std::endl;
    return 1;
  } else {
    path = argv[1];
  }

  // Construct point cloud reader
  spgl::io::LasReadTask readTask(path, true);
  if (!readTask.isReady()) {
    std::cerr << "Invalid input file: " << path << std::endl;
    return 1;
  }

  if (!readTask.open()) {
    std::cerr << "Unable to open file: " << path << std::endl;
    return 1;
  }

  // Read all points from file
  readTask.start();
  readTask.join();
  std::shared_ptr<spgl::gfx3d::PointCloud> pointCloud = readTask.result();

  // Create and initialize render window
  spgl::gfx3d::GlfwRenderWindow renderWindow(true);
  if (!renderWindow.init()) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    return 1;
  }

  // Create window with OpenGL context
  if (!renderWindow.createWindow(640, 480)) {
    std::cerr << "Failed to create window or OpenGL context." << std::endl;

    // Release resources of GLFW
    renderWindow.terminate();
    return 1;
  }

  // Set up camera
  spgl::gfx3d::PerspectiveCamera camera;
  renderWindow.setCamera(&camera);

  // Set up render window interactor
  spgl::gfx3d::PivotInteractor interactor(&renderWindow);
  renderWindow.setInteractor(&interactor);

  // Create point cloud render object
  spgl::gfx3d::PointCloudObject pointCloudObject(std::move(*pointCloud));

  // Create point cloud renderer
  spgl::gfx3d::OGLPointCloudRenderer renderer(&pointCloudObject);
  if (!renderer.isValid()) {
    // Exit
    renderWindow.terminate();
    return 1;
  }

  // Add renderer to window
  renderWindow.addRenderer(&renderer);

  // Point camera to dataset
  interactor.resetCamera();

  // Show window
  renderWindow.show();

  // Destroy window
  renderWindow.destroyWindow();

  // Release resources
  renderWindow.terminate();

  return 0;
}
