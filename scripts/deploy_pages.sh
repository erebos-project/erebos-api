#!/bin/sh

REMOVE="*.cmake CMakeFiles CMakeCache.txt Makefile lib 
        src scripts README.md appveyor.yml 
        .travis.yml sonar-project.properties build_wrapper 
        .gitignore Doxyfile CMakeLists.txt LICENSE "

make docs

#cleanup dirty tree
rm -rfv $REMOVE

#keep html
rm -r doc/latex 

#move html folder
mv doc/html/* . -v


