option (BUILD_DOWNSAMPLER "Build application Downsampler" OFF) 
if (BUILD_DOWNSAMPLER)
	add_subdirectory(Downsampler)
endif (BUILD_DOWNSAMPLER)

option (BUILD_POINTCLOUDVIEWER "Build application Point Cloud Viewer" OFF) 
if (BUILD_POINTCLOUDVIEWER)
	add_subdirectory(PointCloudViewer)
endif (BUILD_POINTCLOUDVIEWER)

option (BUILD_MASSIVEPOINTCLOUDVIEWER "Build application Massive Point Cloud Viewer" OFF) 
if (BUILD_MASSIVEPOINTCLOUDVIEWER)
	add_subdirectory(MassivePointCloudViewer)
endif (BUILD_MASSIVEPOINTCLOUDVIEWER)