########################################################################
# CMake build script for external tools								   #	
########################################################################
project (External_tools) 

########################################################################
# Pobieranie narzêdzi       										   #	
#	S¹ zapisywane w katalogu TMP projektu                              #
########################################################################
# Wersje narzêdzi i katalogi do jakich siê rozpakuj¹, trzeba URL tez zmieniaæ jak by co
set(PANTHEIOS_VER pantheios-1.0.1-beta214 CACHE STRING "")
set(STL_VER stlsoft-1.9.117 CACHE STRING "")

########################################################################
# Patche dla VS12            										   #	
######################################################################## 
MESSAGE(STATUS "Patching sources")
# nazwy musza byæ nadane tu bo dla takich linków by³y nieprawid³owe
execute_process(COMMAND ${WGET_EXECUTABLE} -O PANTH.diff http://sourceforge.net/tracker/download.php?group_id=141831&atid=750759&file_id=456644&aid=3587889 WORKING_DIRECTORY ${TMP})
execute_process(COMMAND ${WGET_EXECUTABLE} -O PANT.zip http://sourceforge.net/tracker/download.php?group_id=141831&atid=750759&file_id=456645&aid=3587889 WORKING_DIRECTORY ${TMP})

########################################################################
# Download STL Pantheios       										   #
#  																	   #	
######################################################################## 	
# jak jest ustawiony projekt na œci¹ganie to œci¹g do source dir
ExternalProject_Add(	STLSoft
						PREFIX ${TMP}
						URL http://sourceforge.net/projects/stlsoft/files/STLSoft%201.9/1.9.117/stlsoft-1.9.117-hdrs.zip
						SOURCE_DIR ${External_tools_SOURCE_DIR}/${STL_VER}
						UPDATE_COMMAND ""
						PATCH_COMMAND ""
						CONFIGURE_COMMAND ""
						BUILD_COMMAND ""
						BUILD_IN_SOURCE 1
						INSTALL_COMMAND ""						
					)	
					
########################################################################
# Kompilacja Pantheios       										   #
# JEst to pe³en projekt, generuje wszystkie wersje libów			   #	
######################################################################## 	
# W zalezonosci od wersji ró¿ne makefile w projekcie
IF (${MSVC_VERSION} EQUAL 1600)	# MSVC10
	set(PANTH_MAKEFILE_PATH build/vc10.x64)
ELSEIF (${MSVC_VERSION} GREATER 1600)	#MSVC11
	set(PANTH_MAKEFILE_PATH build/vc11.x64)
ELSEIF (${CMAKE_COMPILER_IS_GNUCXX})
	
ELSE ()
	MESSAGE(FATAL_ERROR "Setup correct makefile for Pantheios") 	
ENDIF()

# jak jest ustawiony projekt na œci¹ganie to œci¹g do source dir
ExternalProject_Add(	Pantheios
						DEPENDS STLSoft
						PREFIX ${TMP}
						URL http://sourceforge.net/projects/pantheios/files/Pantheios%20%28C%20and%20Cxx%29/1.0.1%20%28beta%20214%29/pantheios-1.0.1-beta214-src.zip
						SOURCE_DIR ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}
						UPDATE_COMMAND ${ZIP_EXECUTABLE} -u ${TMP}/PANT.zip -d ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/build
						PATCH_COMMAND ${PATCH_EXECUTABLE} -p0 -d ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER} -i ${TMP}/PANTH.diff
						CONFIGURE_COMMAND ""
						BUILD_COMMAND cd ${PANTH_MAKEFILE_PATH} && ${CMAKE_BUILD_TOOL}
						BUILD_IN_SOURCE 1
						INSTALL_COMMAND ""						
					)	
########################################################################
# Kompilacja Gtest          										   #	
######################################################################## 
# Add gtest http://stackoverflow.com/questions/9689183/cmake-googletest
# \todo dodaæ set katalogów jak w przyk³adzie http://www.cmake.org/pipermail/cmake/2012-June/050781.html
# \warning Czy biblioteki te bêda do znalezienia automatycznie??
ExternalProject_Add(	googletest
						# wszystko l¹duje w Third_party/Gtest
						PREFIX ${CMAKE_CURRENT_BINARY_DIR}/GTest
						TMP_DIR ${TMP}
						SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
						TIMEOUT 10
						# SOURCE_DIR ${External_tools_SOURCE_DIR}/GTest-src
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_CXX_FLAGS='/D_VARIADIC_MAX=10'
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
							-Dgtest_force_shared_crt=ON
						# BINARY_DIR ${External_tools_SOURCE_DIR}/GTest-bin # bez tej linijki trafia do bin do domyslengo katalogu
						# Disable install step
						INSTALL_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						LOG_DOWNLOAD ON
					)

########################################################################
# Kompilacja BOOST          										   #	
######################################################################## 	
# http://www.boost.org/doc/libs/1_53_0/more/getting_started/windows.html#test-your-program
# linkowanie dynamiczne tylko w windows

# ustawiæ scie¿ki do bibliotek bo ró¿ni¹ siê w zaleznoœci od systemu
IF (${MSVC_VERSION} EQUAL 1600)	# MSVC10
	set(BOOST_TOOLSET msvc-10.0)
	set(BOOST_BOOTSTRAP bootstrap.bat)
	set(BOOST_BUILD_CMD b2)
ELSEIF (${MSVC_VERSION} GREATER 1600)	#MSVC11
	set(BOOST_TOOLSET msvc-11.0)
	set(BOOST_BOOTSTRAP bootstrap.bat)
	set(BOOST_BUILD_CMD b2)
ELSEIF (${CMAKE_COMPILER_IS_GNUCXX})
	set(BOOST_BUILD_CMD ./b2)
	set(BOOST_BOOTSTRAP ./bootstrap.sh)
	set(BOOST_TOOLSET gcc-4.4.5)
ELSE ()
	MESSAGE(FATAL_ERROR "Setup correct makefile for boost") 	
ENDIF()				
set( Boost_Version 1.53.0 )
string( REPLACE "." "_" Boost_Version_Underscore ${Boost_Version} )
message( STATUS "Boost_Version: " ${Boost_Version} )
ExternalProject_Add( 	Boost
						PREFIX ${TMP}
						SOURCE_DIR ${External_tools_SOURCE_DIR}/boost
						URL http://downloads.sourceforge.net/project/boost/boost/${Boost_Version}/boost_${Boost_Version_Underscore}.zip
						UPDATE_COMMAND ${BOOST_BOOTSTRAP}
						CONFIGURE_COMMAND ""
						BUILD_COMMAND ${BOOST_BUILD_CMD} address-model=64 toolset=${BOOST_TOOLSET} link=static stage
						BUILD_IN_SOURCE 1
						INSTALL_COMMAND ""
					)
#set_property( TARGET Boost PROPERTY FOLDER "Externals")
ExternalProject_Get_Property( Boost source_dir )
ExternalProject_Get_Property( Boost binary_dir )
set( Boost_INCLUDE_DIRS ${source_dir} )
set( Boost_LIBRARIES debug;${binary_dir})		
MESSAGE(STATUS ${Boost_INCLUDE_DIRS})	
MESSAGE(STATUS ${Boost_LIBRARIES})			
