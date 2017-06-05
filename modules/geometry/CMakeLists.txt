set(SUBSYS_NAME geometry)
set(SUBSYS_DESC "CHLib geometry processing library")
#Set internal library dependencies, here there isn't other dependencies
set(SUBSYS_DEPS core)

set(build TRUE)
CHLIB_SUBSYS_OPTION(build "${SUBSYS_NAME}" "${SUBSYS_DESC}" ON)
#Add dependencies as well as external dependencies
CHLIB_SUBSYS_DEPEND(build "${SUBSYS_NAME}" DEPS ${SUBSYS_DEPS} EXT_DEPS "")
if(build)
  # Add sources 
  set(srcs
    src/mesh.cpp)
  set(srcs_ext
    ${CHLIB_SOURCE_DIR}/3rdparty/ply/plyfile.c)
  set(incs
    include/chlib/${SUBSYS_NAME}/aabb.hpp
    include/chlib/${SUBSYS_NAME}/mesh.hpp)
  # Set library name
  set(LIB_NAME "chlib_${SUBSYS_NAME}")
  # Add include folder location
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CHLIB_SOURCE_DIR}/3rdparty)

  # Add library
  CHLIB_ADD_LIBRARY("${LIB_NAME}" "${SUBSYS_NAME}" FILES ${srcs} ${incs} ${srcs_ext})

  #EXAMPLES
  IF(WITH_EXAMPLES)
      #LTS5_ADD_EXAMPLE(chlib_video_splitter FILES file LINK_WITH lib)
  ENDIF(WITH_EXAMPLES)

  # TESTS
  #CHLIB_ADD_TEST(cmd_parser chlib_test_cmd_parser FILES test/test_cmd_parser.cpp WORKING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test" ARGUMENTS "" LINK_WITH chlib_core)

  # Install include files
  CHLIB_ADD_INCLUDES("${SUBSYS_NAME}" "${SUBSYS_NAME}" ${incs})
endif(build)
