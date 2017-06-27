//internal usage only
#ifndef PLATFORM_DEFS_H
#define PLATFORM_DEFS_H

#if defined(_WIN32)
#define WINDOWS
#endif
#elif defined(__linux__)
#define LINUX
#endif

#if defined(__clang__)
#define _COMPILER_CLANG
#elif defined(__GNUC__)
#define _COMPILER_GCC
#elif defined(_MSC_VER)
#define _COMPILER_MSVC
#else
#error Unsupported compiler

#endif