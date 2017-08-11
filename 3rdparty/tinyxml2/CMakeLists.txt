# TinyXML2 as External project
# See : https://gist.github.com/oneamtu/3734295

# Enable CMake External project
INCLUDE(ExternalProject)

# set the build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build. Options are: None, Debug, Release, RelWithDebInfo, MinSizeRel"
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)
# Add tinyxml2
ExternalProject_Add(tinyxml_project
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        # TIMEOUT 10
        # # Force separate output paths for debug and release builds to allow easy
        # # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
        # CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
        #            -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
        #            -Dgtest_force_shared_crt=ON
        CMAKE_ARGS -G${CMAKE_GENERATOR} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON -DBUILD_TESTING=OFF -DBUILD_TESTING=OFF
        #CMAKE_CACHE_ARGS -DCMAKE_C_FLAGS:STRING=-fPIC
        # Folder destination
        PREFIX ${OGLKIT_OUTPUT_3RDPARTY_LIB_DIR}/tinyxml
        TMP_DIR ${OGLKIT_OUTPUT_3RDPARTY_LIB_DIR}/tinyxml/tmp
        STAMP_DIR ${OGLKIT_OUTPUT_3RDPARTY_LIB_DIR}/tinyxml/stamp
        DOWNLOAD_DIR ${OGLKIT_OUTPUT_3RDPARTY_LIB_DIR}/tinyxml/download
        SOURCE_DIR ${OGLKIT_OUTPUT_3RDPARTY_LIB_DIR}/tinyxml/src
        BINARY_DIR ${OGLKIT_BINARY_DIR}/lib
        # Disable install step
        INSTALL_COMMAND cmake -E echo "Skipping install step."
        # Wrap download, configure and build steps in a script to log output
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(tinyxml_project source_dir)
SET(TINYXML_INCLUDE_DIR ${source_dir} ${OGLKIT_BINARY_DIR}/lib PARENT_SCOPE)
# Library
ExternalProject_Get_Property(tinyxml_project binary_dir)
SET(TINYXML_LIBRARY_PATH ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}tinyxml2.a)
ADD_LIBRARY(tinyxml STATIC IMPORTED GLOBAL)
SET_PROPERTY(TARGET tinyxml PROPERTY IMPORTED_LOCATION ${TINYXML_LIBRARY_PATH} )
ADD_DEPENDENCIES(tinyxml tinyxml_project)
# Export libraries
SET(TINYXML_LIBRARIES tinyxml PARENT_SCOPE)