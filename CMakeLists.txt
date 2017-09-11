cmake_minimum_required(VERSION 2.8)

project(erebos CXX)

set(COMPILER "Unknown")

set(API_VERSION_MAJOR 0)
set(API_VERSION_MINOR 1)
set(API_VERSION_PATCH 0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif ()

if (NOT LIBRARY)
	if(COMPILER STREQUAL "VCXX")
		set(LIBRARY "shared")
	else()
		set(LIBRARY "static")
	endif()
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(COMPILER "GCC-CLANG" CACHE INTERNAL "")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(COMPILER "GCC-CLANG" CACHE INTERNAL "")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	message("-- MSVC/Suggest: add /EHsc to build flags in order to avoid exception warnings")
	set(COMPILER "VCXX" CACHE INTERNAL "")
else()
	#ya just got killed
	message(FATAL_ERROR "Your compiler identification: ${CMAKE_CXX_COMPILER_ID} is not supported")
endif ()

add_definitions(-DLIBRARY)

find_program(DOXYGEN_EXISTS "doxygen")
if (DOXYGEN_EXISTS)
	add_custom_target(docs doxygen Doxyfile
			DEPENDS "src/version.h"
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

	message("-- Doxygen is available, use 'make docs' to generate docs")
endif ()

add_subdirectory(src)

if(MAKE_TESTS AND LIBRARY STREQUAL "static")
	message("-- Will build tests, use \"test\" target to run tests")
	if(COMPILER STREQUAL "VCXX")
		set(FILE_TARGET "erebos.lib")
	else()
		set(FILE_TARGET "$<TARGET_FILE_NAME:erebos>")
	endif()

	set(EREBOS_STATIC_LIBRARY "$<TARGET_FILE_DIR:erebos>/${FILE_TARGET}" CACHE INTERNAL "")
	include(cmake/Test.cmake)
endif()
