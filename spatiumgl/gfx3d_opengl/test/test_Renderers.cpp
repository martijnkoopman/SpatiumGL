#include <gtest/gtest.h>

#include <spatiumgl/gfx3d/GlfwRenderWindow.hpp>
#include <spatiumgl/gfx3d/PerspectiveCamera.hpp>
#include <spatiumgl/gfx3d/PlaneInteractor.hpp>

#include <spatiumgl/gfx3d/OGLLineMeshRenderer.hpp>

TEST(Renderers, lineRenderer)
{
  // Does not work on Travis CI
  // Create OpenGL context
//  spgl::gfx3d::GlfwRenderWindow renderWindow(true);
//  bool init = renderWindow.init();
//  EXPECT_EQ(init, true);
//  if (!init) {
//    return;
//  }
//  bool window = renderWindow.createWindow(1280, 720);
//  EXPECT_EQ(window, true);
//  if (!window) {
//    renderWindow.terminate();
//    return;
//  }
//  spgl::gfx3d::PerspectiveCamera camera;
//  renderWindow.setCamera(&camera);
//  spgl::gfx3d::PlaneInteractor interactor(&renderWindow);
//  renderWindow.setInteractor(&interactor);

//  // Create line mesh
//  //spgl::gfx3d::LineMesh lineMesh = spgl::gfx3d::LineMesh::quad(1.0f);
//  // spgl::gfx3d::LineMesh lineMesh = spgl::gfx3d::LineMesh::cube(1.0f);
//  spgl::gfx3d::LineMesh lineMesh =
//    spgl::gfx3d::LineMesh::grid(1.0f, { 2, 3 });

  /// \TODO Render to buffer to compare

  //// Create line mesh renderer
  //spgl::gfx3d::OGLLineMeshRenderer lineMeshRenderer(&lineMesh);
  //bool valid = lineMeshRenderer.isValid();
  //if (!valid) {
  //  renderWindow.terminate();
  //  return;
  //}

  //renderWindow.addRenderer(&lineMeshRenderer);
  //interactor.resetCamera();
  //renderWindow.show();
  //renderWindow.destroyWindow();
  //renderWindow.terminate();
}