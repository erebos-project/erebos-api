#!/bin/sh

REMOVE="src scripts README.md appveyor.yml .travis.yml sonar-project.properties build_wrapper .gitignore Doxyfile CMakeLists.txt LICENSE "

make docs

rm -rfv $REMOVE
