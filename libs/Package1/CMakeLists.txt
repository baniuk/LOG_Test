set(LIB_NAME Package1)
project(${LIB_NAME})

include_directories(${External_tools_SOURCE_DIR}/${STL_VER}/include ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/include ${CMAKE_SOURCE_DIR}/libs/includes)
link_directories(${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/lib1)

# biblioteki s¹ domyœlnie budowane jako STATIC, jeœli tego s³owa nie ma w add_library to zale¿y to od zmiennej BUILD_SHARED_LIBS
add_library_with_flags(${LIB_NAME} STATIC "${cxx_flags}" C_Point.cpp)

# Linkowanie w koncowych modu¿ch - test i exe 
# Kolejnosc linkowania ma znaczenie
