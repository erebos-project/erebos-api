@echo off

:usage_and_exit
echo * Usage: %0 ^<version_major^> ^<version_minor^> ^<version_patch^> ^<target_arch^>
exit /B 1


: Configuration

set API_TREE_MAIN_DIRECTORY=".."

set API_VERSION_MAJOR=%1
set API_VERSION_MINOR=%2
set API_VERSION_PATCH=%3
set API_TARGET_ARCH=%4

: NOT WORKING HERE
if %API_VERSION_MAJOR% == "" goto usage_and_exit
if %API_VERSION_MINOR% == "" goto usage_and_exit
if %API_VERSION_PATCH% == "" goto usage_and_exit
if %API_TARGET_ARCH% == ""   goto usage_and_exit

set __REQUIRED__API_HEADER_VERSION_H="src\version.h"
set API_HEADER_PATTERN="src\*.h"
set API_LIBRARY_AR_EREBOS="lib\erebos.lib"
set API_LIBRARY_SHARED_EREBOS="lib\erebos.dll"
set API_README=README.md
set API_LICENSE=LICENSE

set API_PACKAGE_NAME=erebos
set API_PACKAGE_INCLUDE_DIRECTORY=include
set API_PACKAGE_LIBRARY_DIRECTORY=lib
set API_PACKAGE_PLACE_README=1
set API_PACKAGE_PLACE_LICENSE=1
set API_PACKAGE_PLACE_AR=1
set API_PACKAGE_PLACE_SHARED=1
set API_PACKAGE_PLACE_HEADERS=1
set API_PACKAGE_NAME_PATTERN=%API_PACKAGE_NAME%-%API_VERSION_MAJOR%-%API_VERSION_MINOR%-%API_VERSION_PATCH%-windows-%API_TARGET_ARCH%

set SHOULD_EXIT=0

echo /!/ Starting dependency check...

if %API_PACKAGE_PLACE_README% == 1 (
	echo --- README selected
	if exist %API_TREE_MAIN_DIRECTORY%/%API_README% (
		echo ^>^>^> README.md... found
	) else (
		echo !!! README.md... not found
		exit /B 1
	)
)

if %API_PACKAGE_PLACE_LICENSE% == 1 (
	echo --- LICENSE selected
	if exist %API_TREE_MAIN_DIRECTORY%/%API_LICENSE% (
		echo ^>^>^> LICENSE... found
	) else (
		echo !!! LICENSE... not found
		exit /B 1
	)
)

if %API_PACKAGE_PLACE_AR% == 1 (
	echo --- Static library selected
	if exist %API_TREE_MAIN_DIRECTORY%/%API_LIBRARY_AR_EREBOS% (
		echo ^>^>^> Static library... found
	) else (
		echo !!! Static library... not found
		exit /B 1
	)
)

if %API_PACKAGE_PLACE_SHARED% == 1 (
	echo --- Shared library selected
	if exist %API_TREE_MAIN_DIRECTORY%/%API_LIBRARY_SHARED_EREBOS% (
		echo ^>^>^> Shared library... found
	) else (
		echo !!! Shared library... not found
		exit /B 1
	)
)

echo --- (REQUIRED) Checking for generated version.h header...
if not exist %API_TREE_MAIN_DIRECTORY%/%__REQUIRED__API_HEADER_VERSION_H% (
	echo !!! version.h... not found
	echo !!! Configure the build system in order to get the version.h header
)

echo ^>^>^> version.h... found

: powershell.exe -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('dest.zip', 'src'); }"

echo /+/ Ready to build package...
echo /i/ Using PowerShell to make a compressed package

: set_compress_list

: echo /i/ Including the following:
: print_compress_list

: echo /i/ Zipping everything...
: if ! zip -9 $API_PACKAGE_NAME_PATTERN $COMPRESS_LIST (
: 	echo /-/ zip wasn't able to build your package
: 	SHOULD_EXIT=1
: )
: echo /i/ Cleanup...
: temporary_cleanup

: echo /+/ Your package: %API_PACKAGE_NAME_PATTERN% was successfully built
: exit $SHOULD_EXIT

