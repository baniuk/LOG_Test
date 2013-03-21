# Projekt u¿ywa Pantheios
# musi byæ out of source build bo tak to wszystko idzi do katalogu src
project(test_log) 
include_directories(${External_tools_SOURCE_DIR}/${STL_VER}/include ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/include)
link_directories(${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/lib)
add_executable(test_log LOG_test.cpp)

# podczs linkowania do gtest mo¿e treba u¿ycia target_link_ibraries albo po porstu nie rozró¿niac na katalogi podczs budowania gtest.
# JEsli zak³¹damy ¿e podczas kompilacji bêdzie tylko jedna wersj to mo¿e nie trzeba
