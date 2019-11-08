# Point cloud viewer app
option(SPATIUMGL_APP_PCVIEWER "Build app pcviewer." OFF)
if(SPATIUMGL_APP_PCVIEWER)
    add_subdirectory(pcviewer)
endif(SPATIUMGL_APP_PCVIEWER)