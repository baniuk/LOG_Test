set(TESTED_PACKAGE_NAME Package1_test)
project(${TESTED_PACKAGE_NAME}) 

add_dependencies(${TESTED_PACKAGE_NAME} googletest)
ExternalProject_Get_Property(googletest source_dir)
ExternalProject_Get_Property(googletest binary_dir)

include_directories(${source_dir}/include ${External_tools_SOURCE_DIR}/${STL_VER}/include ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/include ${CMAKE_SOURCE_DIR}/libs/includes)
link_directories(${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/lib ${CMAKE_BINARY_DIR}/libs/Package1)

# budowanie exe oraz do³¹czanie wszystkich potrzebnych bibliotek wynikaj¹cych z architektury
IF (${WIN32})
	add_executable_with_flags(${EXE_NAME} Package1 "${cxx_flags}" C_Point_TEST.cpp TESTS.cpp)
ELSEIF ( ${UNIX} )
	add_executable_with_flags(${EXE_NAME} 	"Package1 libpantheios.1.core.gcc44.file64bit.a libpantheios.1.fe.N.gcc44.file64bit.a libpantheios.1.be.N.gcc44.file64bit.a libpantheios.1.bec.file.gcc44.file64bit.a libpantheios.1.bec.fprintf.gcc44.file64bit.a libpantheios.1.util.gcc44.file64bit.a"
											"${cxx_flags}" C_Point_TEST.cpp TESTS.cpp)
ELSE ( ${WIN32} )
	message(FATAL_ERROR "Unknown system")	
ENDIF (${WIN32})

# do³¹czanie bibliotek z gtest
target_link_libraries(${TESTED_PACKAGE_NAME}
                      debug ${binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES} {binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
                      optimized ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}) ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})
					  
add_test( ${TESTED_PACKAGE_NAME} ${TESTED_PACKAGE_NAME} )					  