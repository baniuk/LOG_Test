# macro, adds all subdirs to SUBDIR variable
# automatycznie dodaje wszystkie podkatalogi z tego katlaogu do budowania. Oprócz include
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_LIST_DIR})
FOREACH(subdir ${SUBDIRS})
	IF(NOT ${subdir} MATCHES "include") 
		add_subdirectory(${subdir})
	ENDIF()	
ENDFOREACH()
# add_subdirectory(Package1)