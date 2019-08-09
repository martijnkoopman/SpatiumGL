# SpatiumGL
Graphics library for (geo)spatial visualization based on OpenGL

**Work in progress!**

## Example
```cpp

#include <spatiumgl/io/PointCloudReader.hpp>
#include <spatiumgl/PointCloudRenderer.hpp>

using namespace spatiumgl;

int main()
{
  // Read point cloud 
  PointCloud pointCloud;
  PointCloudReader reader("path/to/las/file.las");
  if (!reader.open())
    return 1;
  reader.readAllPoints(pointCloud);  
  
  // Render point cloud
  GlfwRenderWindow window(40, 480);
  PointCloudRenderer renderer(&pointCloud);
  window.addRenderer(PointCloudRenderer);
  window.show(); 

  return 0;
}
```

## Dependencies (At the moment)
* OpenGL
* GLFW
* GLEW
* GLM
* LASlib

## Building (Windows)
```
# git clone https://github.com/martijnkoopman/SpatiumGL.git

# cd SpatiumGL

# cmake -G "Visual Studio 16 2019" -S SpatiumGL -B SpatiumGL-build ^
-D GLM_INCLUDE_DIR=libs\glm-0.9.9.5\include ^
-D GLEW_INCLUDE_DIR=libs\glew-2.1.0\include -D GLEW_LIBRARY=libs\glew-2.1.0\lib\glew32.lib ^
-D GLFW3_LIBRARY=libs\glfw-3.3\lib\glfw3.lib -D GLFW3_INCLUDE_DIR=libs\glfw-3.3\include ^
-D LASlib_DIR=libs\laslib\lib\cmake\LASlib
```

Then build target ALL_BUILD in the Visual Studio solution. 
