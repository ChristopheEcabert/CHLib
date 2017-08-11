set(SUBSYS_NAME io)
set(SUBSYS_DESC "CHLib I/O library")
#Set internal library dependencies, here there isn't other dependencies
set(SUBSYS_DEPS core)

set(build TRUE)
OGLKIT_SUBSYS_OPTION(build "${SUBSYS_NAME}" "${SUBSYS_DESC}" ON)
#Add dependencies as well as external dependencies
OGLKIT_SUBSYS_DEPEND(build "${SUBSYS_NAME}" DEPS ${SUBSYS_DEPS} EXT_DEPS "")
if(build)
  # Add 3rdparty
  ADD_SUBDIRECTORY(${OGLKIT_SOURCE_DIR}/3rdparty/libjpeg ${OGLKIT_OUTPUT_3RDPARTY_LIB_DIR}/libjpeg)
  ADD_SUBDIRECTORY(${OGLKIT_SOURCE_DIR}/3rdparty/libpng ${OGLKIT_OUTPUT_3RDPARTY_LIB_DIR}/libpng)
  
  # Add sources 
  set(srcs
    src/image_factory.cpp
    src/image.cpp
    src/jpeg_image.cpp
    src/png_image.cpp
    src/tga_image.cpp)
  set(incs
    include/oglkit/${SUBSYS_NAME}/image_factory.hpp
    include/oglkit/${SUBSYS_NAME}/image.hpp
    include/oglkit/${SUBSYS_NAME}/jpeg_image.hpp
    include/oglkit/${SUBSYS_NAME}/png_image.hpp
    include/oglkit/${SUBSYS_NAME}/tga_image.hpp)
  # Set library name
  set(LIB_NAME "oglkit_${SUBSYS_NAME}")
  # Add include folder location
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${LIBPNG_INCLUDE_DIR})
  # Add library
  OGLKIT_ADD_LIBRARY("${LIB_NAME}" "${SUBSYS_NAME}" FILES ${srcs} ${incs} LINK_WITH oglkit_core ${PNG_LIBRARIES} libjpeg)
  ADD_DEPENDENCIES("${LIB_NAME}" libpng libjpeg)
  #EXAMPLES
  IF(WITH_EXAMPLES)
      OGLKIT_ADD_EXAMPLE(oglkit_image_loader FILES example/image_loader.cpp LINK_WITH oglkit_core oglkit_io)
  ENDIF(WITH_EXAMPLES)

  # TESTS
  #OGLKIT_ADD_TEST(cmd_parser oglkit_test_cmd_parser FILES test/test_cmd_parser.cpp WORKING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test" ARGUMENTS "" LINK_WITH oglkit_core)

  # Install include files
  OGLKIT_ADD_INCLUDES("${SUBSYS_NAME}" "${SUBSYS_NAME}" ${incs})
endif(build)
