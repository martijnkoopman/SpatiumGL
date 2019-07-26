# Building PDAL with LAS and LAZ support
This manual targets compiler MSVC 2019 x64, but same procedure will work for other platforms as well, except the procedure for SQLite.

TODO: The following steps should be scripted...

### Dependency tree
* PDAL
  * LASzip
  * GDAL
    * PROJ 
    * GeoTIFF
      * PROJ
      * TIFF

* PROJ
  * SQLite
    * TCL
    
## Build order
1. TCL
2. SQLite
3. PROJ
4. TIFF
5. GeoTIFF
6. GDAL
7. LASzip
8. PDAL

## Building
### TCL
1. Download source code of the latest version (8.6.9) from ..
2. Unpack to any directory (TCL_SOURCE_DIR)
3. Create build directory TCL_SOURCE_DIR/build (TCL_BUILD_DIR)
4. Start 'x64 Native Tools Command Prompt for VS 2019'
5. Change directory to TCL_SOURCE_DIR/win
6. Run: `nmake -f makefile.vc INSTALLDIR=<TCL_BUILD_DIR>` (specify <TCL_BUILD_DIR>)
7. Run: `nmake -f makefile.vc install INSTALLDIR=<TCL_BUILD_DIR>` (specify <TCL_BUILD_DIR>)
8. Rename tclsh86t.exe to tclsh.exe in directory TCL_BUILD_DIR\bin

### SQLite
1. Download source code of the latest version from <https://www.sqlite.org/download.html> (complete source tree, not the amalgamation)
2. Unpack to any directory (SQLITE_SOURCE_DIR)
3. Alter Makefile.msc
  * Set `TCLDIR = <TCL_BUILD_DIR>` (specify <TCL_BUILD_DIR>)
5. Create build directory SQLITE_SOURCE_DIR/build (SQLITE_BUILD_DIR)
6. Start 'x64 Native Tools Command Prompt for VS 2019'
7. Change directory to SQLITE_BUILD_DIR
6. Run: `nmake /f ..\Makefile.msc TOP=.. PLATFORM=x64`
7. Run: `nmake /f ..\Makefile.msc sqlite3.c TOP=.. PLATFORM=x64`
8. Run: `nmake /f ..\Makefile.msc sqlite3.dll TOP=.. PLATFORM=x64`
9. Run: `nmake /f ..\Makefile.msc sqlite3.exe TOP=.. PLATFORM=x64`

### PROJ
1. Download source code of the latest version (6.1.1) from <https://proj.org/download.html>
2. Unpack to any directory (PROJ_SOURCE_DIR)
3. CMake
  * Source dir: PROJ_SOURCE_DIR
  * Build dir: PROJ_SOURCE_DIR/build (PROJ_BUILD_DIR)
  * Generator: Visual Studio 16 2019 x64
  * Specify:
    * BUILD_LIBPROJ_SHARED = True 
    * CMAKE_CONFIGURATION_TYPES = Debug;Release 

    * EXE_SQLITE = <SQLITE_BUILD_DIR>/sqlite3.exe
    * SQLITE3_INCLUDE_DIR = <SQLITE_BUILD_DIR>
    * SQLITE3_LIBRARY = <SQLITE_BUILD_DIR>/sqlite3.lib
  * Generate project
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release, optionally Debug)

### TIFF
1. Download source code of latest version (4.0.9) from <http://download.osgeo.org/libtiff/>
2. Unpack to any directory (TIFF_SOURCE_DIR)
3. CMake
  * Source dir: TIFF_SOURCE_DIR
  * Build dir: TIFF_SOURCE_DIR/build2 (TIFF_BUILD_DIR)
  * Generator: Visual Studio 16 2019 x64
  * Specify:
    * CMAKE_CONFIGURATION_TYPES = Debug;Release
  * Generate project (Ignore support for external codecs)
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release and Debug)
* Copy tiffconf.hpp and tif_config.hpp from TIFF_BUILD_DIR/libtiff to TIFF_SOURCE_DIR/libtiff. (Required for GeoTIFF)

### GeoTIFF
1. Download source code of latest version (1.5.1) from <http://download.osgeo.org/geotiff/libgeotiff/>
2. Unpack to any directory (GEOTIFF_SOURCE_DIR)
3. CMake
  * Source dir: GEOTIFF_SOURCE_DIR
  * Build dir: GEOTIFF_SOURCE_DIR/build
  * Generator: Visual Studio 16 2019 x64
  * Specify:
    * CMAKE_CONFIGURATION_TYPES = Debug;Release
  * Specify TIFF paths:
    * WITH_TIFF = True
    * TIFF_INCLUDE_DIR = <TIFF_SOURCE_DIR>/libtiff
    * TIFF_LIBRARY_DEBUG = <TIFF_BUILD_DIR>/libtiff/Debug/tiffd.lib
    * TIFF_LIBRARY_RELEASE = <TIFF_BUILD_DIR>/libtiff/Release/tiff.lib
  * Specify PROJ paths:
    * PROJ_DIR = PROJ_SOURCE_DIR/cmake
    * PROJ_INCLUDE_DIR = PROJ_SOURCE_DIR/src
    * PROJ_LIBRARY = PROJ_BUILD_DIR/lib/Release/proj_6_1.lib
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release and Debug)

### GDAL
TODO

### LASzip
TODO

### PDAL
TODO