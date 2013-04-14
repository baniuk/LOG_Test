# cmake utils and macros

########################################################################
# Process all subdirectories                                           #
########################################################################
# Example:
#
# SUBDIRLIST(SUBDIRS ${MY_CURRENT_DIR})
# 2) Use foreach:
#
# FOREACH(subdir ${SUBDIRS})
#    ADD_SUBDIRECTORY(${subdir})
# ENDFOREACH()
# makro zakłada ze w danym katalogy wszystkie podkatalogi zawierają pliki cmake.txt
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        SET(dirlist ${dirlist} ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

########################################################################
# Finds all packages                                                   #
########################################################################
MACRO(find_all_required_packages)
	# Common packages
	find_package(Subversion REQUIRED)
	find_package(Doxygen REQUIRED)
	# UNIX
	IF ( ${UNIX} )
#		find_package(wget REQUIRED) # powoduje błędy - nie znaleziono findwget
#		find_package(BZip2 REQUIRED)
	ENDIF ( ${UNIX} )
ENDMACRO()

########################################################################
# Sets additional flags. All are kept in cxx_flags variable that       # 
# contains standard CMake flags and additional flags. Thi variable must#
# be given explicily to every compiled file                            #
########################################################################
MACRO(config_compiler_and_linker)
	# można rozbić na różne zestawy parameetrów - exe, lib, itd
	IF ( ${MSVC} )
		MESSAGE(STATUS "MSVC detected - Adding compiler flags")
		SET(cxx_flags "${CMAKE_CXX_FLAGS} -MP" CACHE STRING "")
	ELSEIF (CMAKE_COMPILER_IS_GNUCXX)
		MESSAGE(STATUS "GCC detected - Adding compiler flags")	
	ENDIF( ${MSVC} )  
ENDMACRO()

########################################################################
# Setting tools                                                        #
########################################################################
MACRO(set_project_tools)
	IF ( ${WIN32} )
		set(WGET_EXECUTABLE ${Test_SOURCE_DIR}/tools/wget.exe CACHE FILEPATH "")
		set(ZIP_EXECUTABLE ${Test_SOURCE_DIR}/tools/unzip.exe CACHE FILEPATH "")
		set(PATCH_EXECUTABLE ${Test_SOURCE_DIR}/tools/patch.exe CACHE FILEPATH "")
	ELSEIF ( ${UNIX} )
		set(WGET_EXECUTABLE wget CACHE FILEPATH "")
		set(ZIP_EXECUTABLE unzip CACHE FILEPATH "")
		set(PATCH_EXECUTABLE patch CACHE FILEPATH "")
	ELSE ( ${WIN32} )
		message(FATAL_ERROR "Unknown system")
	ENDIF ( ${WIN32} )
ENDMACRO()

########################################################################
# Builds library with selsected compilator settings                    #
# Usage: cxx_library(name,type,flags, file1,file2,...)				   #	
########################################################################
function(add_library_with_flags name type cxx_flags)
	# type can be either STATIC or SHARED to denote a static or shared library.
	# ARGN refers to additional arguments after 'cxx_flags'.
	add_library(${name} ${type} ${ARGN})
	set_target_properties(${name}
		PROPERTIES
		COMPILE_FLAGS "${cxx_flags}")
endfunction()

########################################################################
# Builds executable with selsected compilator settings                 #
# Usage: cxx_library(name,libs, flags, file1,file2,...)				   #	
########################################################################
function(add_executable_with_flags name libs cxx_flags)
	# type can be either STATIC or SHARED to denote a static or shared library.
	# ARGN refers to additional arguments after 'cxx_flags'.
	add_executable(${name} ${ARGN})
	set_target_properties(${name}
		PROPERTIES
		COMPILE_FLAGS "${cxx_flags}")
	# To support mixing linking in static and dynamic libraries, link each
	# library in with an extra call to target_link_libraries.
	foreach (lib "${libs}")
		target_link_libraries(${name} ${lib})
	endforeach()	
endfunction()
