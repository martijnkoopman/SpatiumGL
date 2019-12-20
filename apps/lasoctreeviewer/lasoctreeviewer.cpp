#include <spatiumgl/Math.hpp>
#include <spatiumgl/idx/Octree.hpp>
#include <spatiumgl/gfx3d/GlfwRenderWindow.hpp>
#include <spatiumgl/gfx3d/OGLOctreeRenderer.hpp>
#include <spatiumgl/gfx3d/PerspectiveCamera.hpp>
#include <spatiumgl/gfx3d/PivotInteractor.hpp>
#include <spatiumgl/io/LasReadTask.hpp>

#include <iostream>

int
main(int argc, char* argv[])
{
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
  spgl::gfx3d::PivotInteractor interactor(&renderWindow);
  renderWindow.setInteractor(&interactor);

  spgl::idx::Octree octree(spgl::BoundingCube<double>({ 5, 5, 5 }, 5));
  octree.root()->createChild(4);
  octree.root()->child(4)->createChild(5);
  octree.root()->child(4)->child(5)->createChild(6);
  octree.root()->child(4)->child(5)->child(6)->createChild(7);

  // Create point cloud render object
  spgl::gfx3d::OctreeObject octreeObject(std::move(octree)); // move!

  // Create point cloud renderer
  spgl::gfx3d::OGLOctreeRenderer renderer(&octreeObject);
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
