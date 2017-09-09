message("-- Test.cmake")
set(EREBOS_TESTS_LOCATION "${CMAKE_SOURCE_DIR}/test")
set(EREBOS_STATIC_LIBRARY "${CMAKE_SOURCE_DIR}/lib/liberebos.a")
include_directories(${CMAKE_SOURCE_DIR}/src)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "--coverage -Wall -pedantic -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EREBOS_TESTS_LOCATION}")
set(EREBOS_SOURCE_EXT "cpp")
set(EREBOS_TESTS "test-file" 
					  "test-framework"
					  "test-input" 
					  "test-logger"
					  "test-misc" 
					  "test-native"
					  "test-strutils" 
					  "test-time")

enable_testing()
foreach(TEST ${EREBOS_TESTS})
	message(" -- AddTest: ${TEST}")
	add_executable(${TEST} "${EREBOS_TESTS_LOCATION}/${TEST}.${EREBOS_SOURCE_EXT}")
	target_link_libraries(${TEST} gcov ${EREBOS_STATIC_LIBRARY})
	add_dependencies(${TEST} erebos)

	add_test(${TEST} ${EREBOS_TESTS_LOCATION}/${TEST})
endforeach()


