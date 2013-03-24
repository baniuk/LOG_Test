set(LIB_NAME Package1)
project(${LIB_NAME})

include_directories(${External_tools_SOURCE_DIR}/${STL_VER}/include ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/include ${CMAKE_SOURCE_DIR}/libs/includes)
link_directories(${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/lib1)

add_library(${LIB_NAME} STATIC C_Point.cpp)

# explicit linking for UNIX
# Kolejnosc linkowania ma znaczenie
IF (${UNIX})
	target_link_libraries(${LIB_NAME} libpantheios.1.core.gcc44.file64bit.a libpantheios.1.fe.N.gcc44.file64bit.a libpantheios.1.be.N.gcc44.file64bit.a libpantheios.1.bec.file.gcc44.file64bit.a libpantheios.1.bec.fprintf.gcc44.file64bit.a libpantheios.1.util.gcc44.file64bit.a) 
ENDIF (${UNIX})	
