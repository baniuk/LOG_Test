set(LIB_NAME Package1)
project(${LIB_NAME})
 
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src) 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_INCLUDE_DIR})
 
