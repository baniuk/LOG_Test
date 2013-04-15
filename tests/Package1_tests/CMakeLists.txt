set(TESTED_PACKAGE_NAME Package1_test)
project(${TESTED_PACKAGE_NAME}) 

# only for addionale dependencies. Gtest stuff is included inside function
include_directories(${External_tools_SOURCE_DIR}/${STL_VER}/include ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/include ${CMAKE_SOURCE_DIR}/libs/includes)
link_directories(${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/lib ${CMAKE_BINARY_DIR}/libs/Package1)

# budowanie exe testu oraz do³¹czanie wszystkich potrzebnych bibliotek wynikaj¹cych z architektury
IF (${WIN32})
	add_test_with_flags(${TESTED_PACKAGE_NAME} Package1 "${cxx_flags} -D_VARIADIC_MAX=10" C_Point_TEST.cpp TESTS.cpp)
ELSEIF ( ${UNIX} )
	add_test_with_flags(${TESTED_PACKAGE_NAME} "Package1 libpantheios.1.core.gcc44.file64bit.a libpantheios.1.fe.N.gcc44.file64bit.a libpantheios.1.be.N.gcc44.file64bit.a libpantheios.1.bec.file.gcc44.file64bit.a libpantheios.1.bec.fprintf.gcc44.file64bit.a libpantheios.1.util.gcc44.file64bit.a"
											"${cxx_flags} -D_VARIADIC_MAX=10" C_Point_TEST.cpp TESTS.cpp)
ELSE ( ${WIN32} )
	message(FATAL_ERROR "Unknown system")	
ENDIF (${WIN32})

# target jest tworzony po wywo³aniu add_library lub add_exe czyli ta instrukcja musi byæ po tamtych
add_dependencies(${TESTED_PACKAGE_NAME} googletest Package1)
add_test( ${TESTED_PACKAGE_NAME} ${TESTED_PACKAGE_NAME} )					  