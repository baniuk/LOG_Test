# macro, adds all subdirs to SUBDIR variable
# automatycznie dodaje wszystkie podkatalogi z tego katlaogu do budowania.
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_LIST_DIR})
FOREACH(subdir ${SUBDIRS})
	add_subdirectory(${subdir})
ENDFOREACH()
