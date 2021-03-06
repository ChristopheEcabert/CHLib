set(SUBSYS_NAME core)
set(SUBSYS_DESC "OGLKit core element library")
#Set internal library dependencies, here there isn't other dependencies
set(SUBSYS_DEPS)

set(build TRUE)
OGLKIT_SUBSYS_OPTION(build "${SUBSYS_NAME}" "${SUBSYS_DESC}" ON)
#Add dependencies as well as external dependencies
OGLKIT_SUBSYS_DEPEND(build "${SUBSYS_NAME}" DEPS ${SUBSYS_DEPS} EXT_DEPS "")
if(build)
  # Add sources 
  set(srcs
    src/cmd_parser.cpp
    src/error.cpp
    src/string_util.cpp
    src/cmd_parser.cpp)

  set(incs
    include/oglkit/${SUBSYS_NAME}/cmd_parser.hpp
    include/oglkit/${SUBSYS_NAME}/error.hpp
    include/oglkit/${SUBSYS_NAME}/library_export.hpp)
  set(incs_math
    include/oglkit/${SUBSYS_NAME}/math/matrix.hpp
    include/oglkit/${SUBSYS_NAME}/math/quaternion.hpp
    include/oglkit/${SUBSYS_NAME}/math/type_comparator.hpp
    include/oglkit/${SUBSYS_NAME}/math/vector.hpp)
  # Set library name
  set(LIB_NAME "oglkit_${SUBSYS_NAME}")
  # Add include folder location
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

  # Add library
  OGLKIT_ADD_LIBRARY("${LIB_NAME}" "${SUBSYS_NAME}" FILES ${srcs} ${incs} ${incs_math})

  #EXAMPLES
  IF(WITH_EXAMPLES)
      #LTS5_ADD_EXAMPLE(oglkit_video_splitter FILES file LINK_WITH lib)
  ENDIF(WITH_EXAMPLES)

  # TESTS
  OGLKIT_ADD_TEST(cmd_parser oglkit_test_cmd_parser FILES test/test_cmd_parser.cpp WORKING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test" ARGUMENTS "" LINK_WITH oglkit_core)

  # Install include files
  OGLKIT_ADD_INCLUDES("${SUBSYS_NAME}" "${SUBSYS_NAME}" ${incs})
  OGLKIT_ADD_INCLUDES("${SUBSYS_NAME}" "${SUBSYS_NAME}/math" ${incs_math})
endif(build)
