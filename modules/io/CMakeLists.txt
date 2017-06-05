set(SUBSYS_NAME io)
set(SUBSYS_DESC "CHLib I/O library")
#Set internal library dependencies, here there isn't other dependencies
set(SUBSYS_DEPS core)

set(build TRUE)
CHLIB_SUBSYS_OPTION(build "${SUBSYS_NAME}" "${SUBSYS_DESC}" ON)
#Add dependencies as well as external dependencies
CHLIB_SUBSYS_DEPEND(build "${SUBSYS_NAME}" DEPS ${SUBSYS_DEPS} EXT_DEPS "")
if(build)
  # Add 3rdparty
  ADD_SUBDIRECTORY(${CHLIB_SOURCE_DIR}/3rdparty/libjpeg ${CHLIB_OUTPUT_3RDPARTY_LIB_DIR}/libjpeg)
  ADD_SUBDIRECTORY(${CHLIB_SOURCE_DIR}/3rdparty/libpng ${CHLIB_OUTPUT_3RDPARTY_LIB_DIR}/libpng)
  
  # Add sources 
  set(srcs
    src/image_loader.cpp
    src/jpeg_image.cpp
    src/png_image.cpp
    src/tga_image.cpp)
  set(incs
    include/chlib/${SUBSYS_NAME}/image_loader.hpp
    include/chlib/${SUBSYS_NAME}/image.hpp
    include/chlib/${SUBSYS_NAME}/jpeg_image.hpp
    include/chlib/${SUBSYS_NAME}/png_image.hpp
    include/chlib/${SUBSYS_NAME}/tga_image.hpp)
  # Set library name
  set(LIB_NAME "chlib_${SUBSYS_NAME}")
  # Add include folder location
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${LIBPNG_INCLUDE_DIR})
  # Add library
  CHLIB_ADD_LIBRARY("${LIB_NAME}" "${SUBSYS_NAME}" FILES ${srcs} ${incs} LINK_WITH chlib_core ${PNG_LIBRARIES} libjpeg)
  ADD_DEPENDENCIES("${LIB_NAME}" libpng libjpeg)
  #EXAMPLES
  IF(WITH_EXAMPLES)
      CHLIB_ADD_EXAMPLE(chlib_image_loader FILES example/image_loader.cpp LINK_WITH chlib_core chlib_io)
  ENDIF(WITH_EXAMPLES)

  # TESTS
  #CHLIB_ADD_TEST(cmd_parser chlib_test_cmd_parser FILES test/test_cmd_parser.cpp WORKING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test" ARGUMENTS "" LINK_WITH chlib_core)

  # Install include files
  CHLIB_ADD_INCLUDES("${SUBSYS_NAME}" "${SUBSYS_NAME}" ${incs})
endif(build)
