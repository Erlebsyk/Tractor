#option(BUILD_DOC "Build documentation" ON)
#
#if(BUILD_DOC)
#	# Add doxygen documentation if doxygen is installed
#	find_package(Doxygen)
#	if(DOXYGEN_FOUND)
#		add_custom_target(doxygen ALL
#			COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
#			WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
#			COMMENT "Generating API documentation with Doxygen"
#			VERBATIM
#		)
#	else(DOXYGEN_FOUND)
#		message(WARNING "Doxygen not found, documentation will not be generated. Please visit http://www.doxygen.org to download Doxygen.")
#	endif(DOXYGEN_FOUND)
#endif(BUILD_DOC)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM
	)
endif(DOXYGEN_FOUND)