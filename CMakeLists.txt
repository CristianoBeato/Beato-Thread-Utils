#########################################
#	Beato Threading Library -btThread	#
#########################################
#	a multi thread helper library
#	Copyright (c)	2016-2008
#	Cristiano Beato Dos Santos
#	cristianobeato_dm@hotmail.com
#
#----------------------------------------

if(LIB_STATIC)
	set(BUILD_TYPE "_stc")
else()
	set(BUILD_TYPE "_shd")
endif()

set (LIBRARY_NAME "btThread${BUILD_TYPE}")

set(BTHREAD_SOURCE
	source/btAtomic.cpp
	source/btCriticalSection.cpp
	source/btThreadBase.cpp
	source/btPrecompiledHeader.cpp
	source/btErrHandler.cpp
	)

set(BTHREAD_INCLUDE 
	source/btPrecompiledHeader.h
	include/btAtomic.hpp
	include/btCriticalSection.hpp
	include/btThreadBase.hpp
	source/btErrHandler.hpp
	)

	
include_directories(${SDL2_INCLUDE_DIR})
include_directories(include/)

if(USE_PRECOMPILED_HEADERS)
	set(PRECOMPILED_SOURCES ${BTHREAD_SOURCE})
	list(REMOVE_ITEM PRECOMPILED_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/btPrecompiledHeader.cpp)
	if(MSVC)
		set_source_files_properties(btPrecompiledHeader.cpp PROPERTIES COMPILE_FLAGS "/Ycprecompiled.h" OBJECT_OUTPUTS "precompiled.pch")
        set_source_files_properties(${PRECOMPILED_SOURCES} PROPERTIES COMPILE_FLAGS "/Yuprecompiled.h" OBJECT_DEPENDS "precompiled.pch")
	else()
	foreach( src_file ${PRECOMPILED_SOURCES} )
		#message(STATUS "-include precompiled.h for ${src_file}")
		set_source_files_properties(${src_file} PROPERTIES COMPILE_FLAGS "-include ${CMAKE_CURRENT_SOURCE_DIR}/btPrecompiledHeader.h")
	endforeach()
	# precompiled magic for GCC/clang, adapted from https://gist.github.com/573926
	STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
	SET(_compiler_FLAGS ${${_flags_var_name}})
	GET_DIRECTORY_PROPERTY(_directory_flags INCLUDE_DIRECTORIES)
	FOREACH(item ${_directory_flags})
		LIST(APPEND _compiler_FLAGS " -I${item}")
	ENDFOREACH(item)
	
	add_custom_target(precomp_header_idlib ALL COMMAND ${CMAKE_CXX_COMPILER} ${_compiler_FLAGS} -x c++-header btPrecompiledHeader.h -o btPrecompiledHeader.h.gch
	                  WORKING_DIRECTORY ${ }
	                  COMMENT "Creating btThread/precompiled.h.gch for btThread"
	                  )
	
	endif(MSVC)
endif(USE_PRECOMPILED_HEADERS)

#create the library
if(LIB_STATIC)
	add_library(${LIBRARY_NAME}  STATIC ${BTHREAD_SOURCE} ${BTHREAD_INCLUDE})
else()
	add_definitions(-D__BTTH_DLL__)
	add_library(${LIBRARY_NAME}  SHARED ${BTHREAD_SOURCE} ${BTHREAD_INCLUDE})
endif()

if (USE_PRECOMPILED_HEADERS)
		# make sure precompiled header is created before executable is compiled
		add_dependencies(${LIBRARY_NAME} precomp_header_btthread)
endif(USE_PRECOMPILED_HEADERS)