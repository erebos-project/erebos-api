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

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(COMPILER "GCC-CLANG")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(COMPILER "GCC-CLANG")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	message("-- MSVC/Suggest: add /EHsc to build flags in order to avoid exception warnings")
	set(COMPILER "VCXX")
endif ()

add_definitions(-DLIBRARY)

if (COMPILER STREQUAL "Unknown")
	#ya just got killed
	message(FATAL_ERROR "Your compiler identification: ${CMAKE_CXX_COMPILER_ID} is not supported")
endif ()

find_program(DOXYGEN_EXISTS "doxygen")
if (DOXYGEN_EXISTS)
	add_custom_target(docs doxygen Doxyfile
			DEPENDS "src/version.h"
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

	message("-- Doxygen is available, use 'make docs' to generate docs")
endif ()

if(MAKE_TESTS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	include(cmake/Test.cmake)
endif()

add_subdirectory(src)
