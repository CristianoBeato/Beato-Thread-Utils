# file CMakeLists.txt
#########################################
#	Beato Threading Library -btThread	#
#########################################
#	a multi thread helper library
#	Copyright (c)	2016-2008
#	Cristiano Beato Dos Santos
#	cristianobeato_dm@hotmail.com
#
#----------------------------------------
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)

#project name
project(Beato-Thread-Utils)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


option(USE_PRECOMPILED_HEADERS			"Use precompiled headers to speedup buld" ON)
option(BUILD_SHARED						"Build a shared lib istead of sharead static linked lib" ON)
option(BUILD_SAMPLES					"Build exemple samples" ON)

#build mode
if(BUILD_SHARED)
	add_definitions(-D__BTTH_DLL__)
	set(BUILD_TYPE "_shd")
	set(BUILD_MODE SHARED)
else()
	add_definitions(-D__BTTH_STC__)
	set(BUILD_TYPE "_stc")
	set(BUILD_MODE STATIC)
endif()

set (LIBRARY_NAME "btThread${BUILD_TYPE}")

#search for sdl for low level interface 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(BTHREAD_SOURCE
	source/btAtomic.cpp
	source/btCriticalSection.cpp
	source/btThreadBase.cpp
	source/precompiled.cpp
	source/btErrHandler.cpp
	source/btInstrusivePointer.cpp
	)

set(BTHREAD_INCLUDE 
	include/beatoThread.hpp
	source/precompiled.h
	include/btAtomic.hpp
	include/btCriticalSection.hpp
	include/btThreadBase.hpp
	source/btErrHandler.hpp
	include/btCommon.hpp
	include/btInstrusivePointer.hpp
	)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(include/)

if(BUILD_SAMPLES)
	add_subdirectory(samples)
endif(BUILD_SAMPLES)

if(USE_PRECOMPILED_HEADERS)
	set(PRECOMPILED_SOURCES ${BTHREAD_SOURCE})
	list(REMOVE_ITEM PRECOMPILED_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/precompiled.cpp)
	if(MSVC)
		set_source_files_properties(precompiled.cpp PROPERTIES COMPILE_FLAGS "/Ycprecompiled.h" OBJECT_OUTPUTS "precompiled.pch")
        set_source_files_properties(${PRECOMPILED_SOURCES} PROPERTIES COMPILE_FLAGS "/Yuprecompiled.h" OBJECT_DEPENDS "precompiled.pch")
	else(MINGW)
		foreach( src_file ${PRECOMPILED_SOURCES} )
			#message(STATUS "-include precompiled.h for ${src_file}")
			set_source_files_properties(${src_file} PROPERTIES COMPILE_FLAGS "-include ${CMAKE_CURRENT_SOURCE_DIR}/precompiled.h")
		endforeach()
		# precompiled magic for GCC/clang, adapted from https://gist.github.com/573926
		STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
		SET(_compiler_FLAGS ${${_flags_var_name}})
		GET_DIRECTORY_PROPERTY(_directory_flags INCLUDE_DIRECTORIES)
		FOREACH(item ${_directory_flags})
			LIST(APPEND _compiler_FLAGS " -I${item}")
		ENDFOREACH(item)
	
		add_custom_target(precomp_header_btthread ALL COMMAND ${CMAKE_CXX_COMPILER} ${_compiler_FLAGS} -x c++-header precompiled.h -o precompiled.h.gch
						WORKING_DIRECTORY ${ }
						COMMENT "Creating btThread/precompiled.h.gch for btThread")
	endif(MSVC)
endif(USE_PRECOMPILED_HEADERS)

#create the library
add_library(${LIBRARY_NAME} ${BUILD_MODE} ${BTHREAD_SOURCE} ${BTHREAD_INCLUDE})
target_link_libraries(${LIBRARY_NAME} ${SDL2_LIBRARIES})

if (USE_PRECOMPILED_HEADERS)
	if(NOT MSVC)
		# make sure precompiled header is created before executable is compiled
		add_dependencies(${LIBRARY_NAME} precomp_header_btthread)
	endif(NOT MSVC)
endif(USE_PRECOMPILED_HEADERS)