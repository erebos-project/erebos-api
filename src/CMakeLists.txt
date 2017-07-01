cmake_minimum_required(VERSION 2.8)

#find_package if required
configure_file("${PROJECT_SOURCE_DIR}/src/version.h.in" "${PROJECT_SOURCE_DIR}/src/version.h")

set(CMAKE_CXX_STANDARD 11)

if(COMPILER STREQUAL "VCXX")
	message("-- Compiler/OS match... OK")
else()
	if(COMPILER STREQUAL "GCC-CLANG" AND UNIX AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
		message("-- Compiler/OS match... OK")
	elseif(COMPILER STREQUAL "GCC-CLANG" AND WIN32)
		message("-- Compiler/OS match... OK")
	else()
		message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is currently not supported, aborting...")
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

set(SOURCES framework.cpp native.cpp logger.cpp time.cpp file.cpp)

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

if(UNIX AND LIBRARY STREQUAL "shared")
	install(TARGETS erebos LIBRARY
			DESTINATION ${CMAKE_PREFIX_DIR}/lib)
elseif(UNIX AND LIBRARY STREQUAL "static")
	install(TARGETS erebos ARCHIVE
			DESTINATION ${CMAKE_PREFIX_DIR}/lib)
endif()

if(UNIX)
	install(FILES *.h DESTINATION ${CMAKE_PREFIX_DIR}/include/erebos
		PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)
endif()
