/*!
 * @file platform_defs.h
 * @brief You should not include this explicitly.
 */
#ifndef PLATFORM_DEFS_H
#define PLATFORM_DEFS_H

#if defined(_WIN32)
#define WINDOWS
#elif defined(__linux__)
#define LINUX
#else
#error Unsupported operating system
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


// We have to add this macro before EVERY function declaration because M$ was too lazy
#if defined(_COMPILER_MSVC) && defined(LIBRARY)
#define ERAPI __declspec(dllexport)
#else
#define ERAPI
#endif

#endif
