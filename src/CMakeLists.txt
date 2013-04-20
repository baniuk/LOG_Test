# Projekt u¿ywa Pantheios
# musi byæ out of source build bo tak to wszystko idzi do katalogu src
set(EXE_NAME test_log)
project(${EXE_NAME}) 
include_directories(${External_tools_SOURCE_DIR}/${STL_VER}/include ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/include ${CMAKE_SOURCE_DIR}/libs/includes)
link_directories(${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/lib)


# explicit linking for UNIX
# Kolejnosc linkowania ma znaczenie
IF (${WIN32})
	add_executable_with_flags(${EXE_NAME} Package1 "${cxx_flags}" LOG_test.cpp)	# Package jest linkowane bo cmake zna katalog z lib (nie trzeba dodawaæ w link_directories)
ELSEIF ( ${UNIX} )
	add_executable_with_flags(${EXE_NAME} 	"Package1 libpantheios.1.core.gcc44.file64bit.a libpantheios.1.fe.N.gcc44.file64bit.a libpantheios.1.be.N.gcc44.file64bit.a libpantheios.1.bec.file.gcc44.file64bit.a libpantheios.1.bec.fprintf.gcc44.file64bit.a libpantheios.1.util.gcc44.file64bit.a"
											"${cxx_flags}" LOG_test.cpp)
ELSE ( ${WIN32} )
	message(FATAL_ERROR "Unknown system")	
ENDIF (${WIN32})	
# podczs linkowania do gtest mo¿e treba u¿ycia target_link_ibraries albo po porstu nie rozró¿niac na katalogi podczs budowania gtest.
# JEsli zak³¹damy ¿e podczas kompilacji bêdzie tylko jedna wersj to mo¿e nie trzeba
# target_link_libraries(${EXE_NAME} Package1)
