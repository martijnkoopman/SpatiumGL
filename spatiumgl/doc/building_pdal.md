

# Fetching PDAL dependencies
conda install -c conda-forge gdal
conda install -c conda-forge gdal

# Building PDAL dependencies
This manual targets Visual Studio 2019 16.1 x64 (MSVC++ 14.21; 1921), but the same procedure will work for other platforms as well, except the procedure for SQLite.

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
4. curl
5. TIFF
6. GeoTIFF
7. GDAL
8. LASzip
9. PDAL

## Building
### TCL
1. Download source code of the latest version (8.6.9) from <https://www.tcl.tk/software/tcltk/download.html>
2. Unpack to any directory (TCL_SOURCE_DIR)
3. Create build directory `TCL_SOURCE_DIR/build` (TCL_BUILD_DIR)
4. Start 'x64 Native Tools Command Prompt for VS 2019'
5. Change directory to `TCL_SOURCE_DIR/win`
6. Run: `nmake -f makefile.vc INSTALLDIR=<TCL_BUILD_DIR>` (specify <TCL_BUILD_DIR>)
7. Run: `nmake -f makefile.vc install INSTALLDIR=<TCL_BUILD_DIR>` (specify <TCL_BUILD_DIR>)
8. Rename `tclsh86t.exe` to `tclsh.exe` in directory `TCL_BUILD_DIR\bin`

### SQLite
1. Download source code of latest version (3290000) from <https://www.sqlite.org/download.html> (complete source tree, not the amalgamation)
3. Unpack to any directory (SQLITE_SOURCE_DIR)
4. Alter `Makefile.msc`
  * Set `TCLDIR = <TCL_BUILD_DIR>` (specify <TCL_BUILD_DIR>)
5. Create build directory `SQLITE_SOURCE_DIR/build` (SQLITE_BUILD_DIR)
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
  * Source dir: `PROJ_SOURCE_DIR`
  * Build dir: `PROJ_SOURCE_DIR/build` (PROJ_BUILD_DIR)
  * Generator: Visual Studio 16 2019 x64
  * Specify:
    * `BUILD_LIBPROJ_SHARED = True`
    * `CMAKE_CONFIGURATION_TYPES = Debug;Release`
    * `CMAKE_INSTALL_PREFIX = <PROJ_BUILD_DIR>/install` (PROJ_INSTALL_DIR)
  * Specify SQLite
    * `EXE_SQLITE = <SQLITE_BUILD_DIR>/sqlite3.exe`
    * `SQLITE3_INCLUDE_DIR = <SQLITE_BUILD_DIR>`
    * `SQLITE3_LIBRARY = <SQLITE_BUILD_DIR>/sqlite3.lib`
  * Generate project
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release, optionally Debug)
  * Build project INSTALL

### curl
1. Download source code of the latest version (7.65.3) from <https://curl.haxx.se/download.html>
2. Unpack to any directory (CURL_SOURCE_DIR)
3. CMake
  * Source dir: `CURL_SOURCE_DIR`
  * Build dir: `CURL_SOURCE_DIR/build` (CURL_BUILD_DIR)
  * Generator: Visual Studio 16 2019 x64* 
  * Specify:
    * `CMAKE_CONFIGURATION_TYPES = Debug;Release`
    * `CMAKE_INSTALL_PREFIX = <CURL_BUILD_DIR>/install` (CURL_INSTALL_DIR)
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release and Debug)
  * Build project INSTALL

### TIFF
1. Download source code of latest version (4.0.9) from <http://download.osgeo.org/libtiff/>
2. Unpack to any directory (TIFF_SOURCE_DIR)
3. CMake
  * Source dir: `TIFF_SOURCE_DIR`
  * Build dir: `TIFF_SOURCE_DIR/build2` (TIFF_BUILD_DIR)
  * Generator: Visual Studio 16 2019 x64
  * Specify:
    * `CMAKE_CONFIGURATION_TYPES = Debug;Release`
    * `CMAKE_INSTALL_PREFIX = <TIFF_BUILD_DIR>/install` (TIFF_INSTALL_DIR)
  * Generate project (Ignore support for external codecs)
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release and Debug)
  * Build project INSTALL

### GeoTIFF
1. Download source code of latest version (1.5.1) from <http://download.osgeo.org/geotiff/libgeotiff/>
2. Unpack to any directory (GEOTIFF_SOURCE_DIR)
3. CMake
  * Source dir: `GEOTIFF_SOURCE_DIR`
  * Build dir: `GEOTIFF_SOURCE_DIR/build` (GEOTIFF_BUILD_DIR)
  * Generator: Visual Studio 16 2019 x64
  * Specify:
    * `CMAKE_CONFIGURATION_TYPES = Debug;Release`
    * `CMAKE_INSTALL_PREFIX = <GEOTIFF_BUILD_DIR>/install` (GEOTIFF_INSTALL_DIR)
  * Specify TIFF paths:
    * WITH_TIFF = True
    * `TIFF_INCLUDE_DIR = <TIFF_INSTALL_DIR>/include`
    * `TIFF_LIBRARY_DEBUG = <TIFF_INSTALL_DIR>/lib/tiffd.lib`
    * `TIFF_LIBRARY_RELEASE = <TIFF_INSTALL_DIR>/lib/tiff.lib`
  * Specify PROJ paths:
    * `PROJ_INCLUDE_DIR = <PROJ_INSTALL_DIR>/include`
    * `PROJ_LIBRARY = <PROJ_INSTALL_DIR>/lib/proj_6_1.lib`
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release and Debug)


### GDAL
1. Download source code of the latest version (3.0.1) from 
2. Unpack to any directory (GDAL_SOURCE_DIR)
3. Create build directory `GDAL_SOURCE_DIR/build` (GDAL_BUILD_DIR). 
4. Alter `nmake.opt` (Specify <***>):
* `CURL_DIR = <CURL_INSTALL_DIR>`
* `CURL_LIB = $(CURL_DIR)/lib/libcurl_imp.lib wsock32.lib wldap32.lib winmm.lib`
* `PROJ_INCLUDE = -I<PROJ_INSTALL_DIR>\include`
* `PROJ_LIB = <PROJ_INSTALL_DIR>\lib\proj_6_1.lib`
* `TIFF_INC =  -I<TIFF_INSTALL_DIR>\include`
* `TIFF_LIB =  <TIFF_INSTALL_DIR>\lib\tiff.lib`
* `GEOTIFF_INC = -I<GEOTIFF_INSTALL_DIR>\include`
* `GEOTIFF_LIB = <GEOTIFF_INSTALL_DIR>\lib\geotiff.lib`
* 
5. Run: `nmake -f makefile.vc MSVC_VER=1921 WIN64=1 GDAL_HOME=<GDAL_BUILD_DIR>`
5. Run: `nmake -f makefile.vc install MSVC_VER=1921 WIN64=1 GDAL_HOME=<GDAL_BUILD_DIR>`
6. Run: `nmake -f makefile.vc devinstall MSVC_VER=1921 WIN64=1 GDAL_HOME=<GDAL_BUILD_DIR>`

### LASzip
1. Download source code of the latest version (3.2.8) from  <https://laszip.org/>
2. Unpack to any directory (LASZIP_SOURCE_DIR)
3. CMake
  * Source dir: `LASZIP_SOURCE_DIR`
  * Build dir: `LASZIP_SOURCE_DIR/build` (LASZIP_BUILD_DIR)
  * Generator: Visual Studio 16 2019 x64
  * Specify:
    * `CMAKE_CONFIGURATION_TYPES = Debug;Release`
    * `CMAKE_INSTALL_PREFIX = <LASZIP_BUILD_DIR>/install`
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release and Debug)
  * Build project INSTALL

### PDAL
1. Download source code of the latest version (1.9.1) from <https://pdal.io/download.html>
2. Unpack to any directory (PDAL_SOURCE_DIR)
3. Start 'x64 Native Tools Command Prompt for VS 2019'
4. Change directory to PDAL_SOURCE_DIR
5. Start CMake. Run: `cmake-gui`
6. CMake
  * Source dir: `PDAL_SOURCE_DIR`
  * Build dir: `PDAL_SOURCE_DIR/build` (PDAL_BUILD_DIR)
  * Generator: Visual Studio 16 2019 x64
  * Specify:
    * `CMAKE_CONFIGURATION_TYPES = Debug;Release`
    * `CMAKE_INSTALL_PREFIX = <PDAL_BUILD_DIR>/install`
    * `WITH_ZLIB = False`
  * Specify CURL paths:
    * `CURL_INCLUDE_DIR = <CURL_INSTALL_DIR>/include`
    * `CURL_LIBRARY = <CURL_INSTALL_DIR>/lib/libcurl_imp.lib`
  * Specify LASzip paths:
    * `LASZIP_INCLUDE_DIR = <LASZIP_INSTALL_DIR>/include`
    * `LASZIP_LIBRARY = <LASZIP_INSTALL_DIR>/lib/laszip3.lib`
  * Specify GDAL paths:
    * `GDAL_INCLUDE_DIR = <GDAL_BUILD_DIR>/include`
    * `GDAL_LIBRARY = <GDAL_BUILD_DIR>/lib/gdal_i.lib`
  * Specify GeoTIFF paths:
    * `GEOTIFF_INCLUDE_DIR = <GEOTIFF_INSTALL_DIR>/include`
    * `GEOTIFF_LIBRARY = <GEOTIFF_INSTALL_DIR>/lib/geotiff.lib`
* Compile
  * Open generated solution
  * Build project BUILD_ALL (Release and Debug)
  * Build project INSTALL

Expected CMake output:
```
Selecting Windows SDK version 10.0.17134.0 to target Windows 10.0.17763.
Could NOT find JSONCPP (missing: JSONCPP_LIBRARY JSONCPP_INCLUDE_DIR) (Required is at least version "1.6.2")
Could NOT find LibXml2 (missing: LIBXML2_LIBRARY LIBXML2_INCLUDE_DIR) 
Could NOT find LIBEXECINFO (missing: LIBEXECINFO_LIBRARY LIBEXECINFO_INCLUDE_DIR) 
Could NOT find LIBUNWIND (missing: LIBUNWIND_LIBRARY LIBUNWIND_INCLUDE_DIR) 
The following features have been enabled:

 * Unit tests, PDAL unit tests

-- The following OPTIONAL packages have been found:

 * Curl
 * PythonInterp

-- The following RECOMMENDED packages have been found:

 * LASzip (required version >= 3.1)
   Provides LASzip compression
   Provides LASzip compression

-- The following REQUIRED packages have been found:

 * GDAL (required version >= 2.2.0)
   Provides general purpose raster, vector, and reference system support
 * GeoTIFF
 * Threads, The thread library of the system

-- The following features have been disabled:

 * Bash completion, completion for PDAL command line
 * CPD plugin, Coherent Point Drift (CPD) computes rigid or nonrigid transformations between point sets
 * GeoWave plugin, Read and Write data using GeoWave
 * I3S plugin, Read from a I3S server or from a SLPK file
 * Greyhound plugin, read points from a Greyhound server
 * Icebridge plugin, read data in the Icebridge format
 * Matlab plugin, write data to a .mat file
 * MrSID plugin, read data in the MrSID format
 * NITF plugin, read/write LAS data wrapped in NITF
 * OpenSceneGraph plugin, read/write OpenSceneGraph objects
 * Oracle OCI plugin, Read/write point clould patches to Oracle
 * PCL plugin, provides PCL-based readers, writers, filters, and kernels
 * PostgreSQL PointCloud plugin, read/write PostgreSQL PointCloud objects
 * SQLite plugin, read/write SQLite objects
 * RiVLib plugin, read data in the RXP format
 * rdblib plugin, read data in the RDB format
 * Python plugin, add features that depend on python
 * MBIO plugin, add features that depend on MBIO
 * FBX plugin, add features that depend on FBX
 * TileDB plugin, read/write data from TileDB

-- The following OPTIONAL packages have not been found:

 * PostgreSQL
 * JSONCPP (required version >= 1.6.2)
 * PkgConfig
 * LibXml2
 * Libexecinfo
 * Libunwind

Configuring done
```