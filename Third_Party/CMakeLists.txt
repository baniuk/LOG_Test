########################################################################
# CMake build script for external tools								   #	
########################################################################
project (External_tools) 

########################################################################
# Pobieranie narz�dzi       										   #	
#	S� zapisywane w katalogu TMP projektu                              #
########################################################################
# Wersje narz�dzi i katalogi do jakich si� rozpakuj�
set(PANTHEIOS_VER pantheios-1.0.1-beta214 CACHE STRING "")
set(STL_VER stlsoft-1.9.117 CACHE STRING "")
# pobieranie stlsoft 
execute_process(COMMAND ${WGET_EXECUTABLE} -N http://sourceforge.net/projects/stlsoft/files/STLSoft%201.9/1.9.117/stlsoft-1.9.117-hdrs.zip/download
					WORKING_DIRECTORY ${TMP})
# pobieranie Pantheios				
execute_process(COMMAND ${WGET_EXECUTABLE} -N http://sourceforge.net/projects/pantheios/files/Pantheios%20%28C%20and%20Cxx%29/1.0.1%20%28beta%20214%29/pantheios-1.0.1-beta214-src.zip/download
				WORKING_DIRECTORY ${TMP})
# wypakowywanie				
execute_process(COMMAND ${ZIP_EXECUTABLE} -u ${TMP}/${STL_VER}-hdrs.zip -d ${External_tools_SOURCE_DIR}) 	
execute_process(COMMAND ${ZIP_EXECUTABLE} -u ${TMP}/${PANTHEIOS_VER}-src.zip -d ${External_tools_SOURCE_DIR})
########################################################################
# Patche dla VS12            										   #	
######################################################################## 
IF ( ${MSVC} )
	MESSAGE(STATUS "Patching sources")
	# nazwy musza by� nadane tu bo dla takich link�w by�y nieprawid�owe
	execute_process(COMMAND ${WGET_EXECUTABLE} -O STL.diff http://sourceforge.net/tracker/download.php?group_id=238860&atid=1107748&file_id=456643&aid=3587881 WORKING_DIRECTORY ${TMP})
	execute_process(COMMAND ${WGET_EXECUTABLE} -O PANTH.diff http://sourceforge.net/tracker/download.php?group_id=141831&atid=750759&file_id=456644&aid=3587889 WORKING_DIRECTORY ${TMP})
	execute_process(COMMAND ${WGET_EXECUTABLE} -O PANT.zip http://sourceforge.net/tracker/download.php?group_id=141831&atid=750759&file_id=456645&aid=3587889 WORKING_DIRECTORY ${TMP})
	
	execute_process(COMMAND ${ZIP_EXECUTABLE} -u ${TMP}/PANT.zip -d ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/build) 	
	execute_process(COMMAND ${PATCH_EXECUTABLE} -p0 -d ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER} -i ${TMP}/PANTH.diff) 	
	execute_process(COMMAND ${PATCH_EXECUTABLE} -p0 -d ${External_tools_SOURCE_DIR}/${STL_VER} -i ${TMP}/STL.diff) 
ENDIF ( ${MSVC} )
	
########################################################################
# Kompilacja Pantheios       										   #
# JEst to pe�en projekt, generuje wszystkie wersje lib�w			   #	
######################################################################## 	
# W zalezonosci od wersji r�ne makefile w projekcie
IF (${MSVC_VERSION} EQUAL 1600)	# MSVC10
	set(PANTH_MAKEFILE_PATH build/vc10.x64)
ELSEIF (${MSVC_VERSION} GREATER 1600)	#MSVC11
	set(PANTH_MAKEFILE_PATH build/vc11.x64)
ELSE (${MSVC_VERSION} GREATER 1600)
	MESSAGE(FATAL_ERROR "Setup correct makefile fo Pantheios") 	
ENDIF(${MSVC_VERSION} EQUAL 1600)
ExternalProject_Add(	Pantheios
						PREFIX ${TMP}
						TMP_DIR ${TMP}
						STAMP_DIR ${TMP}
						SOURCE_DIR ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/${PANTH_MAKEFILE_PATH}
						CONFIGURE_COMMAND ""
						BUILD_COMMAND ${MAKE}
						BUILD_IN_SOURCE 1
						INSTALL_COMMAND ""						
					)	
########################################################################
# Kompilacja Gtest          										   #	
######################################################################## 
# Add gtest http://stackoverflow.com/questions/9689183/cmake-googletest

ExternalProject_Add(
					googletest-read-only
					TMP_DIR ${TMP}
					STAMP_DIR ${External_tools_SOURCE_DIR}/GTest-stamp
					SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
					TIMEOUT 10
					SOURCE_DIR ${External_tools_SOURCE_DIR}/GTest-src
					# Force separate output paths for debug and release builds to allow easy
					# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
					CMAKE_ARGS -DCMAKE_CXX_FLAGS='/D_VARIADIC_MAX=10'
						-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
						-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
						-Dgtest_force_shared_crt=ON
					BINARY_DIR ${External_tools_SOURCE_DIR}/GTest-bin
					# Disable install step
					INSTALL_COMMAND ""
					# Wrap download, configure and build steps in a script to log output
					LOG_DOWNLOAD ON
					)