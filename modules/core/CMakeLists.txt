set(SUBSYS_NAME core)
set(SUBSYS_DESC "CHLib core element library")
#Set internal library dependencies, here there isn't other dependencies
set(SUBSYS_DEPS)

set(build TRUE)
CHLIB_SUBSYS_OPTION(build "${SUBSYS_NAME}" "${SUBSYS_DESC}" ON)
#Add dependencies as well as external dependencies
CHLIB_SUBSYS_DEPEND(build "${SUBSYS_NAME}" DEPS ${SUBSYS_DEPS} EXT_DEPS "")
if(build)
  # Add sources 
  set(srcs
    src/cmd_parser.cpp
    src/error.cpp
    src/string_util.cpp
    src/cmd_parser.cpp)

  set(incs
    include/chlib/${SUBSYS_NAME}/cmd_parser.hpp
    include/chlib/${SUBSYS_NAME}/error.hpp
    include/chlib/${SUBSYS_NAME}/library_export.hpp)
  set(incs_math
    include/chlib/${SUBSYS_NAME}/math/matrix.hpp
    include/chlib/${SUBSYS_NAME}/math/quaternion.hpp
    include/chlib/${SUBSYS_NAME}/math/type_comparator.hpp
    include/chlib/${SUBSYS_NAME}/math/vector.hpp)
  # Set library name
  set(LIB_NAME "chlib_${SUBSYS_NAME}")
  # Add include folder location
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

  # Add library
  CHLIB_ADD_LIBRARY("${LIB_NAME}" "${SUBSYS_NAME}" FILES ${srcs} ${incs} ${incs_math})

  #EXAMPLES
  IF(WITH_EXAMPLES)
      #LTS5_ADD_EXAMPLE(chlib_video_splitter FILES file LINK_WITH lib)
  ENDIF(WITH_EXAMPLES)

  # TESTS
  CHLIB_ADD_TEST(cmd_parser chlib_test_cmd_parser FILES test/test_cmd_parser.cpp WORKING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test" ARGUMENTS "" LINK_WITH chlib_core)

  # Install include files
  CHLIB_ADD_INCLUDES("${SUBSYS_NAME}" "${SUBSYS_NAME}" ${incs})
  CHLIB_ADD_INCLUDES("${SUBSYS_NAME}" "${SUBSYS_NAME}/math" ${incs_math})
endif(build)
