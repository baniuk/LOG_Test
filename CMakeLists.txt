########################################################################
# CMake build script for LOG_test.									   #
########################################################################
# Possible targets:
# gtest_main gtest	- from gtest

cmake_minimum_required (VERSION 2.8) 
########################################################################
# Finding required packages                                            #
########################################################################
find_package(Subversion REQUIRED)
find_package(Doxygen REQUIRED)

########################################################################
# Setting tools                                                        #
########################################################################
IF ( ${WIN32} )
	set(WGET_EXECUTABLE ${Test_SOURCE_DIR}/tools/wget.exe CACHE FILEPATH "")
	set(ZIP_EXECUTABLE ${Test_SOURCE_DIR}/tools/unzip.exe CACHE FILEPATH "")
	set(PATCH_EXECUTABLE ${Test_SOURCE_DIR}/tools/patch.exe CACHE FILEPATH "")
ELSEIF ( ${UNIX} )
	# automatyczne szukanie narz�dzi, ustawia te same zmienne co wy�ej
ELSE ( ${UNIX} )
	message(FATAL_ERROR "Unknown system")
ENDIF ( ${WIN32} )

########################################################################
# Setup project                                                        #
########################################################################
include(ExternalProject)
# Project name - nazwa jako zmienna bo u�ywana tez w doxygenie
set(PROJECT_NAME "Test" CACHE STRING "")
project (${PROJECT_NAME}) 

# TMP dirs
file(MAKE_DIRECTORY CMake_trash)
set(TMP ${Test_SOURCE_DIR}/CMake_trash CACHE PATH "")

# Set default ExternalProject root directory http://stackoverflow.com/questions/9689183/cmake-googletest
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${Test_BINARY_DIR}/Third_Party)

########################################################################
# Building external libraries   (targrt gtest, all)                    #
########################################################################
add_subdirectory(Third_Party)	

########################################################################
# Building Doxygen DOC     (targrt doc, all)                           #
########################################################################
add_subdirectory(Configs)

#include_directories(${CMAKE_ROOT}/external/stlsoft-1.9.116/include)
#set( ENV{STLSOFT}  ${CMAKE_CURRENT_BINARY_DIR}/stlsoft-1.9.116)

add_subdirectory(src)

########################################################################
# Create warper makefile with external env                             #
########################################################################
file(WRITE ${TMP}/make_wrapper_script.bat "rem Warper makefile created autmoaticly\n" )
file(APPEND ${TMP}/make_wrapper_script.bat "set STLSOFT=${External_tools_SOURCE_DIR}/${STL_VER}\n")
file(APPEND ${TMP}/make_wrapper_script.bat "nmake\n")
