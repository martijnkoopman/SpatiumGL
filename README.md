# SpatiumGL [![Build Status](https://travis-ci.org/martijnkoopman/SpatiumGL.svg?branch=master)](https://travis-ci.org/martijnkoopman/SpatiumGL)
C++ graphics library for (geo)spatial visualization.

## Content
### Modules
* core - Core classes (Vector, Matrix, Image) and functionality (math, statistics, constants)
* gfx3d - 3D graphics (generic)
* gfx3d_opengl - 3D graphics implementation based on OpenGL
* io_las - LAS/LAZ point cloud IO.

### Module dependency graph
![Architecture](https://g.gravizo.com/svg?digraph%20G%20%7B%0Asubgraph%20cluster_0%20%7B%0Aspatiumgl%20-%3E%20core%3B%0Aspatiumgl%20-%3E%20gfx3d%3B%0Aspatiumgl%20-%3E%20gfx3d_opengl%3B%0Aspatiumgl%20-%3E%20io_las%3B%0Agfx3d%20-%3E%20core%3B%0Agfx3d_opengl%20-%3E%20gfx3d%3B%0Aio_las%20-%3E%20core%3B%0A%7B%20rank%3Dsame%20core%20gfx3d%2C%20gfx3d_opengl%2C%20io_las%20%7D%0Alabel%20%3D%20%22SpatiumGL%22%3B%0Alabelloc%3Dt%3B%0Alabeljust%3Dl%3B%0A%7D%0Aapp%20%5Blabel%3D%22Your%20app%22%2C%20shape%3Dbox%2C%20style%3Dfilled%2C%20fillcolor%3Dblack%2C%20fontcolor%3Dwhite%5D%3B%0Aapp%20-%3E%20spatiumgl%3B%0AOpenGL%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dlightgrey%5D%3B%0AGLFW%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dlightgrey%5D%3B%0AGLEW%5Bstyle%3Dfilled%2C%20fillcolor%3Dlightgrey%5D%3B%0Agfx3d_opengl%20-%3E%20OpenGL%3B%0Agfx3d_opengl%20-%3E%20GLFW%3B%0Agfx3d_opengl%20-%3E%20GLEW%3B%0ALASlib%20%5Bstyle%3Dfilled%2C%20fillcolor%3Dlightgrey%5D%3B%0Aio_las-%3E%20LASlib%3B%0A%7D%0A%7D)

### Apps
* lasviewer - LAS/LAZ Point cloud viewer

### Namespaces
* spatiumgl
  * gfx3d - 3D graphics
  * io - File input/output
  
## Building the library
**Clone or download this repository**

```
$ git clone https://github.com/martijnkoopman/SpatiumGL
$ cd SpatiumGL
```

**Create build directory**

```
$ mkdir build
$ cd build
```

**Run CMake**

Linux, macOS

```
$ cmake .. -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=ON -DSPATIUMGL_MODULE_GFX3D=ON -DSPATIUMGL_MODULE_GFX3D_OPENGL=ON -DSPATIUMGL_MODULE_IO_LAS=ON -DSPATIUMGL_APP_LASVIEWER=ON
```
Windows
```
$ cmake .. -G "Visual Studio 16 2019 Win64" -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=ON -DSPATIUMGL_MODULE_GFX3D=ON -DSPATIUMGL_MODULE_GFX3D_OPENGL=ON -DSPATIUMGL_MODULE_IO_LAS=ON -DSPATIUMGL_APP_LASVIEWER=ON
```

*CMake options*

| Option        | Effect           | 
| ------------- | ------------- |
| BUILD_SHARED_LIBS | Build as shared library (versus static) |
| BUILD_TESTING | Build unit tests |
| SPATIUMGL_MODULE_GFX3D | Include module gfx3d | 
| SPATIUMGL_MODULE_GFX3D_OPENGL | Include module gfx3d_opengl | 
| SPATIUMGL_MODULE_IO_LAS | Include module io_las | 
| SPATIUMGL_APP_LASVIEWER | Include app lasviewer |

## Using the library
...

## License
GPL
