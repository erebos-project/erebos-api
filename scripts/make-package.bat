@echo off

set API_TREE_MAIN_DIRECTORY=".."

set API_VERSION_MAJOR=%1
set API_VERSION_MINOR=%2
set API_VERSION_PATCH=%3
set API_TARGET_ARCH=%4
set USE_MINGW=%5

: Check that arguments exist
if "%API_TARGET_ARCH%" == "" (
	goto usage_and_exit
)

: Configuration

set API_HEADER_VERSION_H="src\version.h"
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


if "%USE_MINGW%" == "1" (
	set API_LIBRARY_AR_EREBOS="lib\liberebos.a"
	set API_LIBRARY_SHARED_EREBOS="lib\liberebos.so"
)


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
if exist %API_TREE_MAIN_DIRECTORY%/%API_HEADER_VERSION_H% (
	echo ^>^>^> version.h... found
) else (
	echo !!! version.h... not found
	echo !!! Configure the build system in order to get the version.h header
	exit /B 1
)


echo /+/ Ready to build package...

:set_compress_list

mkdir %API_PACKAGE_NAME_PATTERN%

if "%API_PACKAGE_PLACE_README%" == "1" (
	copy /Y %API_TREE_MAIN_DIRECTORY%\%API_README% %API_PACKAGE_NAME_PATTERN%\ >nul
)

if "%API_PACKAGE_PLACE_LICENSE%" == "1" (
	copy /Y %API_TREE_MAIN_DIRECTORY%\%API_LICENSE% %API_PACKAGE_NAME_PATTERN%\ >nul
)

mkdir %API_PACKAGE_NAME_PATTERN%\%API_PACKAGE_LIBRARY_DIRECTORY% >nul

if "%API_PACKAGE_PLACE_AR%" == "1" (
	copy /Y %API_TREE_MAIN_DIRECTORY%\%API_LIBRARY_AR_EREBOS% %API_PACKAGE_NAME_PATTERN%\%API_PACKAGE_LIBRARY_DIRECTORY% >nul
)

if "%API_PACKAGE_PLACE_SHARED%" == "1" (
	copy /Y %API_TREE_MAIN_DIRECTORY%\%API_LIBRARY_SHARED_EREBOS% %API_PACKAGE_NAME_PATTERN%\%API_PACKAGE_LIBRARY_DIRECTORY% >nul
)

if "%API_PACKAGE_PLACE_HEADERS%" == "1" (
	mkdir %API_PACKAGE_NAME_PATTERN%\%API_PACKAGE_INCLUDE_DIRECTORY% >nul
	copy /Y %API_TREE_MAIN_DIRECTORY%\%API_HEADER_PATTERN% %API_PACKAGE_NAME_PATTERN%\%API_PACKAGE_INCLUDE_DIRECTORY% >nul
)

if errorlevel 1 (
	echo /-/ An error occurred while copying files
	exit /B 1
)

echo /i/ Zipping everything...
echo /i/ Using PowerShell to make a compressed package

if exist %API_PACKAGE_NAME_PATTERN%.zip (
	del %API_PACKAGE_NAME_PATTERN%.zip
)

powershell.exe -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.fileSystem'; [IO.Compression.Zipfile]::CreateFromDirectory('%API_PACKAGE_NAME_PATTERN%', '%API_PACKAGE_NAME_PATTERN%.zip'); }"

if errorlevel 1 (
	echo /-/ Powershell wasn't able to build your package
	rmdir /S/Q %API_PACKAGE_NAME_PATTERN%
	exit /B 1
)

:temporary_cleanup
echo /i/ Cleanup...
: Delete temp dir
rmdir /S/Q %API_PACKAGE_NAME_PATTERN%

echo /+/ Your package: %API_PACKAGE_NAME_PATTERN% was successfully built

exit /B 0

:usage_and_exit
echo * Usage: %0 ^<version_major^> ^<version_minor^> ^<version_patch^> ^<target_arch^> ^<use mingw^>
exit /B 1
