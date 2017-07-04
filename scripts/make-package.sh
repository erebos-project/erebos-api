#!/bin/sh

if [ $# -lt 3 ]; then
	echo " * Usage: $0 <version_tag> <target_os> <target_arch> [ignored...]"
	exit 1
fi

#Configuration

API_TREE_MAIN_DIRECTORY=".."

API_VERSION_TAG=$1
API_TARGET_OS=$4
API_TARGET_ARCH=$5

__REQUIRED__API_HEADER_VERSION_H="src/version.h"
API_HEADER_PATTERN="src/*.h"
API_LIBRARY_AR_EREBOS="lib/liberebos.a"
API_LIBRARY_SHARED_EREBOS="lib/liberebos.so"
API_README="README.md"
API_LICENSE="LICENSE"

API_PACKAGE_NAME="erebos"
API_PACKAGE_INCLUDE_DIRECTORY="include"
API_PACKAGE_LIBRARY_DIRECTORY="lib"
API_PACKAGE_PLACE_README=true
API_PACKAGE_PLACE_LICENSE=true
API_PACKAGE_PLACE_AR=true
API_PACAKGE_PLACE_SHARED=true
API_PACAKGE_PLACE_HEADERS=true
API_PACKAGE_NAME_PATTERN="${API_PACKAGE_NAME}-${API_VERSION_TAG}-${API_TARGET_OS}-${API_TARGET_ARCH}"

check_depends() {
	if $API_PACKAGE_PLACE_README; then
		echo "--- README selected"
		if [ -f $API_TREE_MAIN_DIRECTORY/$API_README ]; then
			echo ">>> README.md... found"
		else
			echo "!!! README.md... not found"
			exit 1
		fi
	fi

	if $API_PACKAGE_PLACE_LICENSE; then
		echo "--- LICENSE selected"
		if [ -f $API_TREE_MAIN_DIRECTORY/$API_LICENSE ]; then
			echo ">>> LICENSE... found"
		else
			echo "!!! LICENSE... not found"
			exit 1
		fi
	fi

	if $API_PACKAGE_PLACE_AR; then
		echo "--- Static library selected"
		if [ -f $API_TREE_MAIN_DIRECTORY/$API_LIBRARY_AR_EREBOS ]; then
			echo ">>> Static library... found"
		else
			echo "!!! Static library... not found"
			exit 1
		fi
	fi

	if $API_PACKAGE_PLACE_SHARED; then
		echo "--- Shared library selected"
		if [ -f $API_TREE_MAIN_DIRECTORY/$API_LIBRARY_SHARED_EREBOS ]; then
			echo ">>> Shared library... found"
		else
			echo "!!! Shared library... not found"
			exit 1
		fi
	fi

	if $API_PACKAGE_PLACE_HEADERS; then
		echo "--- Development headers selected"
		if ls $API_TREE_MAIN_DIRECTORY/$API_HEADER_PATTERN 2>/dev/null >>/dev/null; then
			echo ">>> Development headers... found"
		else
			echo "!!! Development headers... not found"
			exit 1
		fi
	fi

	echo "--- (REQUIRED) Checking for generated version.h header..."
	if [ ! -f $API_TREE_MAIN_DIRECTORY/$__REQUIRED__API_HEADER_VERSION_H ]; then
		echo "!!! version.h... not found"
		echo "!!! Configure the build system in order to get the version.h header"
		exit 1
	fi

	echo ">>> version.h... found"
}

check_zip() {
	echo "--- Checking for zip program..."
	if ! which zip 2>/dev/null >>/dev/null; then
		echo "!!! zip: not found in PATH environment variable"
		exit 1
	fi
	echo ">>> zip... found"
}

COMPRESS_LIST=""
set_compress_list() {

	if $API_PACKAGE_PLACE_README; then
		cp $API_TREE_MAIN_DIRECTORY/$API_README .
		COMPRESS_LIST="$API_README"
	fi

	if $API_PACKAGE_PLACE_LICENSE; then
		cp $API_TREE_MAIN_DIRECTORY/$API_LICENSE .
		COMPRESS_LIST="$COMPRESS_LIST $API_LICENSE"
	fi

	if $API_PACKAGE_PLACE_AR; then
		mkdir -p $API_PACKAGE_LIBRARY_DIRECTORY
		cp $API_TREE_MAIN_DIRECTORY/$API_LIBRARY_AR_EREBOS $API_PACKAGE_LIBRARY_DIRECTORY
		COMPRESS_LIST="$COMPRESS_LIST $API_PACKAGE_LIBRARY_DIRECTORY/*"
	fi

	if $API_PACKAGE_PLACE_SHARED; then
		if [ ! -d $API_PACKAGE_LIBRARY_DIRECTORY ]; then
			COMPRESS_LIST="$COMPRESS_LIST $API_PACKAGE_LIBRARY_DIRECTORY/*"
		fi

		mkdir -p $API_PACKAGE_LIBRARY_DIRECTORY
		cp $API_TREE_MAIN_DIRECTORY/$API_LIBRARY_SHARED_EREBOS $API_PACKAGE_LIBRARY_DIRECTORY
	fi

	if $API_PACKAGE_PLACE_HEADERS; then
		mkdir -p $API_PACKAGE_INCLUDE_DIRECTORY
		cp $API_TREE_MAIN_DIRECTORY/$API_HEADER_PATTERN $API_PACKAGE_INCLUDE_DIRECTORY
		COMPRESS_LIST="$COMPRESS_LIST $API_PACKAGE_INCLUDE_DIRECTORY/*"
	fi
}

print_compress_list() {
	for i in $COMPRESS_LIST; do
		echo " > f: $i"
	done
}

temporary_cleanup() {
	rm -rf $COMPRESS_LIST 2>/dev/null
	for elem in $COMPRESS_LIST; do
		rm -r $(echo $elem | sed 's:/::') 2>/dev/null
	done
}

SHOULD_EXIT=0
echo "/!/ Starting dependency check..."
check_depends
echo "/+/ Ready to build package..."
echo "/i/ Using zip"
check_zip
set_compress_list
echo "/i/ Including the following:"
print_compress_list
echo "/i/ Zipping everything..."
if ! zip -9 $API_PACKAGE_NAME_PATTERN $COMPRESS_LIST; then
	echo "/-/ zip wasn't able to build your package"
	SHOULD_EXIT=1
fi
echo "/i/ Cleanup..."
temporary_cleanup
echo "/+/ Your package: ${API_PACKAGE_NAME_PATTERN} was successfully built"
exit $SHOULD_EXIT
