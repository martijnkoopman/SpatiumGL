#include <spatiumgl/Math.hpp>
#include <spatiumgl/gfx3d/GlfwRenderWindow.hpp>
#include <spatiumgl/gfx3d/OGLPointCloudRenderer.hpp>
#include <spatiumgl/gfx3d/PerspectiveCamera.hpp>
#include <spatiumgl/gfx3d/PlaneInteractor.hpp>
#include <spatiumgl/gfx3d/PointCloud.hpp>
#include <spatiumgl/gfx3d/PointCloudObject.hpp>
#include <spatiumgl/io/LasReadTask.hpp>
#include <spatiumgl/io/LasUtils.hpp>

#include "CLI11.hpp"

#include <iostream>

enum ColoringMethod : int
{
  Classification, // unsigned short
  GpsTime,        // double
  Intensity,      // unsigned short
  NumberOfReturns,
  PointSourceID,
  RGB,
  ReturnNumber,
  ScanAngle,
  UserData,
  X,
  Y,
  Z
};

int
main(int argc, char* argv[])
{
  // Parse command-line arguments
  CLI::App app{ "View LAS/LAZ point cloud in 3D." };
  std::string fileIn;
  app.add_option("-i,--input", fileIn, "Input LAS/lAZ file")
    ->required()
    ->check(CLI::ExistingFile);

  ColoringMethod coloringMethod;
  std::vector<std::pair<std::string, ColoringMethod>> map{
    { "classification", ColoringMethod::Classification },
    { "gps-time", ColoringMethod::GpsTime },
    { "intentsity", ColoringMethod::Intensity },
    { "number-of-returns", ColoringMethod::NumberOfReturns },
    { "point-source-id", ColoringMethod::PointSourceID },
    { "return-number", ColoringMethod::ReturnNumber },
    { "rgb", ColoringMethod::RGB },
    { "scan-angle", ColoringMethod::ScanAngle },
    { "user-data", ColoringMethod::UserData }
  };
  app.add_option("-c,--color", coloringMethod, "Coloring method")
    ->required()
    ->transform(
      CLI::CheckedTransformer(map, CLI::ignore_case).description("color in {classification, gps-time, intentsity, number-of-returns, point-source-id, return-number, rgb, scan-angle, user-data}"));

  CLI11_PARSE(app, argc, argv)

  // Construct point cloud reader
  spgl::io::LasReadTask readTask(fileIn, true);
  std::string error = readTask.validate();
  if (!error.empty()) {
    std::cerr << error << std::endl;
    return 1;
  }

  std::cout << "Point count to read: " << readTask.lasReader().lasHeader().number_of_point_records << std::endl;
  std::cout << "Point cloud has color: "
            << (spgl::io::LasUtils::formatHasRgb(readTask.lasReader().lasHeader().point_data_format) ? "Yes" : "No") << std::endl;

  // Read all points from file
  readTask.start();

  // Print progress every second
  int progress = 0;
  while (readTask.isRunning()) {
    // Sleep for 1 second
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Check and print progress if updated
    int currentProgress = readTask.progress().percentage();
    if (currentProgress > progress) {
      int dots = currentProgress - progress;
      for (int i = 0; i < dots; i++) {
        std::cout << "." << std::flush;
	  }
      progress = currentProgress;
    }
  }
  std::cout << std::endl;

  // Join with read task
  readTask.join();
 
  std::shared_ptr<spgl::gfx3d::PointCloud> pointCloud = readTask.result();
  if (pointCloud == nullptr) {
    std::cerr << "Error reading point cloud." << std::endl;
    return 1;
  }

  std::cout << "Point cloud size: "
            << std::to_string(pointCloud->data().computeSize()) << " bytes"
            << std::endl;

  // Create and initialize render window
  spgl::gfx3d::GlfwRenderWindow renderWindow(true);
  if (!renderWindow.init()) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    return 1;
  }

  // Create window with OpenGL context
  if (!renderWindow.createWindow(1280, 720)) {
    std::cerr << "Failed to create window or OpenGL context." << std::endl;

    // Release resources of GLFW
    renderWindow.terminate();
    return 1;
  }

  // Set up camera
  spgl::gfx3d::PerspectiveCamera camera;
  renderWindow.setCamera(&camera);

  // Set up render window interactor
  spgl::gfx3d::PlaneInteractor interactor(&renderWindow);
  renderWindow.setInteractor(&interactor);

  // Create point cloud render object
  spgl::gfx3d::PointCloudObject pointCloudObject(std::move(*pointCloud)); // move!

  spgl::gfx3d::PointCloudRenderOptions renderOptions;
  renderOptions.pointSize = 0.20f;
  renderOptions.pointScaleWorld = true;

  // Create point cloud renderer
  spgl::gfx3d::OGLPointCloudRenderer renderer(&pointCloudObject, renderOptions);
  if (!renderer.isValid()) {
    // Exit
    renderWindow.terminate();
    return 1;
  }

  pointCloudObject.pointCloud().data().clear();

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
