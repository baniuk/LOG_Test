set(LIB_NAME Package1)
project(${LIB_NAME})
 
include_directories(${CMAKE_SOURCE_DIR}/libs/includes)
 
add_library(${LIB_NAME} STATIC C_Point.cpp)