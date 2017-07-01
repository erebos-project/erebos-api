#!/bin/sh

REMOVE="src scripts README.md appveyor.yml .travis.yml sonar-project.properties build-wrapper"

make docs

rm -rfv $REMOVE
