# Projekt u¿ywa Pantheios
# musi byæ out of source build bo tak to wszystko idzi do katalogu src
project(test_log) 
include_directories(${External_tools_SOURCE_DIR}/${STL_VER}/include ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/include ${CMAKE_SOURCE_DIR}/libs/includes)
link_directories(${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/lib ${CMAKE_BINARY_DIR}/libs/Package1)
add_executable(test_log LOG_test.cpp)

# explicit linking for UNIX
# Kolejnosc linkowania ma znaczenie
IF (${UNIX})
	target_link_libraries(test_log libpantheios.1.core.gcc44.file64bit.a libpantheios.1.fe.N.gcc44.file64bit.a libpantheios.1.be.N.gcc44.file64bit.a libpantheios.1.bec.file.gcc44.file64bit.a libpantheios.1.bec.fprintf.gcc44.file64bit.a libpantheios.1.util.gcc44.file64bit.a) 
ENDIF (${UNIX})	
# podczs linkowania do gtest mo¿e treba u¿ycia target_link_ibraries albo po porstu nie rozró¿niac na katalogi podczs budowania gtest.
# JEsli zak³¹damy ¿e podczas kompilacji bêdzie tylko jedna wersj to mo¿e nie trzeba
target_link_libraries(test_log Package1)