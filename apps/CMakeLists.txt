# Point cloud viewer app
option(SPATIUMGL_APP_HELLO "Build app hello." OFF)
if(SPATIUMGL_APP_HELLO)
    add_subdirectory(hello)
endif(SPATIUMGL_APP_HELLO)

# Point cloud viewer app
option(SPATIUMGL_APP_PCVIEWER "Build app pcviewer." OFF)
if(SPATIUMGL_APP_PCVIEWER)
    add_subdirectory(pcviewer)
endif(SPATIUMGL_APP_PCVIEWER)

# Point cloud info app
option(SPATIUMGL_APP_PCINFO "Build app pcinfo." OFF)
if(SPATIUMGL_APP_PCINFO)
    add_subdirectory(pcinfo)
endif(SPATIUMGL_APP_PCINFO)