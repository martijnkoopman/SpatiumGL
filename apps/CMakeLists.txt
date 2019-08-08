option (BUILD_POINTCLOUD_INFO "Build application pcinfo" OFF) 
if (BUILD_POINTCLOUD_INFO)
	add_subdirectory(pcinfo)
endif (BUILD_POINTCLOUD_INFO)

option (BUILD_POINTCLOUD_GRIDSAMPLER "Build application pcgridsampler" OFF) 
if (BUILD_POINTCLOUD_GRIDSAMPLER)
	add_subdirectory(pcgridsampler)
endif (BUILD_POINTCLOUD_GRIDSAMPLER)

option (BUILD_POINTCLOUD_VIEWER "Build application pcviewer" OFF) 
if (BUILD_POINTCLOUD_VIEWER)
	add_subdirectory(pcviewer)
endif (BUILD_POINTCLOUD_VIEWER)

option (BUILD_POINTCLOUD_OCTREEVIEWER "Build application pcoctreeviewer" OFF) 
if (BUILD_POINTCLOUD_OCTREEVIEWER)
	add_subdirectory(pcoctreeviewer)
endif (BUILD_POINTCLOUD_OCTREEVIEWER)