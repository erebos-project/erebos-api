#!/usr/bin/env python
# compile.py
# Compiles all the programs in src folder.
# Uses GCC and supports Linux and Windows (with MinGW installed).
import sys
import os
import glob

platform_define = "LINUX"
lib_folder = "linux"

if sys.platform == "win32":
	platform_define = "WIN32"
	lib_folder = "win32"
	pass

print("Compiling Erebos framework...")
os.system("g++ src/*.cpp -shared -std=c++11 -Iinclude -D" + platform_define + " -Llib/" + lib_folder + " -o bin/liberebos.so")

print("Complete!")
