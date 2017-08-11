IF(WITH_DOCS)
    #Find doxygen
    FIND_PACKAGE(Doxygen REQUIRED)
    IF(DOXYGEN_FOUND)
        #Add documentation target
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/oglkit_doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
        COMMENT "Generating API documentation with Doxygen" VERBATIM)
        #Add install
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc/oglkit-${OGLKIT_MAJOR_VERSION}.${OGLKIT_MINOR_VERSION} CONFIGURATIONS Release;RelWithDebInfo)
    ENDIF(DOXYGEN_FOUND)
ENDIF(WITH_DOCS)
