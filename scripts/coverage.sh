#!/bin/bash

BUILD_DIRECTORY=$1
COVERAGE_DEST=$2
PATTERN_TEST_TARGET="${BUILD_DIRECTORY}/CMakeFiles/test-*.dir/test/*.cpp.*"
PATTERN_LIB_TARGET="${BUILD_DIRECTORY}/src/CMakeFiles/erebos.dir/*.cpp.*"
TESTS_EXEC_DIR="../test"
TESTS="file framework strutils time logger input misc native"

mkdir -p $COVERAGE_DEST
cp $PATTERN_TEST_TARGET $COVERAGE_DEST
cp $PATTERN_LIB_TARGET $COVERAGE_DEST

cd $COVERAGE_DEST
find . -name '*.cpp.*' -type f | 
	while read NAME ; do 
		mv "${NAME}" "${NAME/.cpp/}"
	done

rm *.o

for test in $TESTS; do
	mv "${TESTS_EXEC_DIR}/test-$test" .
done

gcov "*.gcno"
