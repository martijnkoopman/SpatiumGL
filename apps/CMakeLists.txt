# LAS/LAZ point cloud viewer app
option(SPATIUMGL_APP_LASVIEWER "Build app lasviewer." OFF)
if(SPATIUMGL_APP_LASVIEWER)
    add_subdirectory(lasviewer)
endif(SPATIUMGL_APP_LASVIEWER)
