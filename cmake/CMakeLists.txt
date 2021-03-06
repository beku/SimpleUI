#
# Target installation folders
#

SET (TARGET_INCLUDE_FOLDER
		"simpleui"
		CACHE STRING
		"Optional folder below system include folder to install include files."
    )

SET (TARGET_CMAKE_FOLDER
		"share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules"
		CACHE STRING
		"The folder below system prefix where to install cmake files."
    )

SET (TARGET_PLUGIN_FOLDER "simpleui"
		CACHE STRING
		"Optional folder below system library folder where to install simpleui plugins. LIB_SUFFIX is honored."
    )

SET (TARGET_PKGCONFIG_FOLDER
		"pkgconfig"
		CACHE STRING
		"The folder below system library folder where to install pkgconfig files. LIB_SUFFIX is honored."
    )

SET (TARGET_DOCUMENTATION_FOLDER
		"share/doc/simpleui-api"
		CACHE STRING
		"The folder below system prefix where to install api documentation files."
    )


#
# Misc.
#

SET (LIB_SUFFIX ""
		CACHE STRING
		"Optional suffix to use on lib folders (e.g. 64 for lib64)"
    )
#cmake settings for use by find_package
CONFIGURE_FILE (
		"${CMAKE_CURRENT_SOURCE_DIR}/SimpleUiConfig.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/SimpleUiConfig.cmake"
		@ONLY
	)

INSTALL ( FILES
		"${CMAKE_CURRENT_BINARY_DIR}/SimpleUiConfig.cmake"
		DESTINATION lib${LIB_SUFFIX}/simpleui/cmake COMPONENT dev
	)

