# LAS/LAZ point cloud info app
option(SPATIUMGL_APP_LASINFO "Build app lasinfo." OFF)
if(SPATIUMGL_APP_LASINFO)
    add_subdirectory(lasinfo)
endif(SPATIUMGL_APP_LASINFO)

# LAS/LAZ point cloud viewer app
option(SPATIUMGL_APP_LASVIEWER "Build app lasviewer." OFF)
if(SPATIUMGL_APP_LASVIEWER)
    add_subdirectory(lasviewer)
endif(SPATIUMGL_APP_LASVIEWER)

# LAS/LAZ point cloud thin app
option(SPATIUMGL_APP_LASOCTREEVIEWER "Build app lasoctree and lasoctreeviewer." OFF)
if(SPATIUMGL_APP_LASOCTREEVIEWER)
    add_subdirectory(lasoctree)
    add_subdirectory(lasoctreeviewer)
endif(SPATIUMGL_APP_LASOCTREEVIEWER)
