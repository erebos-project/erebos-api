cmake_minimum_required(VERSION 2.8)

#find_package if required

set(CMAKE_CXX_STANDARD 11)

if(COMPILER STREQUAL "VCXX")
	add_definitions(/DWINDOWS)
else()
	if(COMPILER STREQUAL "GCC-CLANG" AND UNIX)
		add_definitions(-DLINUX)
	elseif(COMPILER STREQUAL "GCC-CLANG" AND WIN32)
		add_definitions(-DWINDOWS)
	endif()
endif()

if(COMPILER STREQUAL "VCXX")
	set(CMAKE_CXX_FLAGS_DEBUG "/EHsc /Z7 /W3")
elseif(COMPILER STREQUAL "GCC-CLANG")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -Wall -W -Wextra ")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("-- Debugging build, higher warning level (3) and debugging symbols included")
	if(COMPILER STREQUAL "VCXX")
		add_definitions(/DDEBUG)
	elseif(COMPILER STREQUAL "GCC-CLANG")
		add_definitions(-DDEBUG)
	endif()
endif()

set(SOURCES framework.cpp native.cpp)

if(NOT LIBRARY)
	set(LIBRARY "static")
endif()

if(LIBRARY STREQUAL "shared")
	message("-- Shared library")
	add_library(erebos SHARED ${SOURCES})
else()
	message("-- Static library")
	add_library(erebos STATIC ${SOURCES})
endif()
