/*
* framework.h
* Erebos API providing common utility functions.
* Includes 'native.h' and 'stringutils.h'
* All functions should be cross-platform.
*/

#ifndef _FRAMEWORK_H
#define _FRAMEWORK_H

#include "platform_defs.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <utility>

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
#include <cstdlib>
#endif

#include "ftypes.h"
#include "version.h"

/*
* DEFVERSION(int MAJOR, int MINOR, int PATCH) macro for defining a program's version easily.
* e.g. DEFVERSION(1, 0, 0)
*/
#define DEFVERSION(MAJOR, MINOR, PATCH) \
	constexpr int VERSION_MAJOR = MAJOR; \
	constexpr int VERSION_MINOR = MINOR; \
	constexpr int VERSION_PATCH = PATCH

/*
* FUNCALIAS(NEWNAME, OLDNAME) macro for defining an alias for a function.
*/
#define FUNCALIAS(NEWNAME, OLDNAME) \
	constexpr auto NEWNAME = OLDNAME

/*
* VERSIONFUNC(progname) macro for automatic version printing.
* Prints the program's version (defined with DEFVERSION) if the '-version' or '-v' argument is passed.
* The caller should have the "args" variable defined (as a Args).
* e.g.
* DEFVERSION(1, 0, 0)
* VERSIONFUNC(program)
* prints:
*
* program v1.0.0
*
*/
#define VERSIONFUNC(progname) \
	if(args.contains_s("-version") { \
		std::stringstream ss; \
		ss << "\n" << progname << "\t" << "v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH; \
		std::cout << ss.str() << std::endl; \
		exit(0); \
	}

namespace erebos {
	/*
	* std::string get_api_version()
	* Returns Erebos' API version as a string in the format MAJOR.MINOR.PATCH .
	*/
	inline std::string get_api_version() {
		std::stringstream ss;
		ss << API_VERSION_MAJOR << "." << API_VERSION_MINOR << "." << API_VERSION_PATCH;
		return ss.str();
	}

	/*
	* int hex_to_int(std::string str)
	* Converts the specified hex-like string to int.
	*/
	inline int hex_to_int(const std::string& str) {
		int res;
		std::stringstream ss(str);
		ss >> std::hex >> res;
		return res;
	}

	/*
	* std::string var_to_string(T var)
	* Converts the given variable into a string.
	* Some implementations don't provide 'to_string'.
	* This is a simple template to replace it.
	*/
	template<typename T>
	inline std::string var_to_string(const T& var) {
		std::stringstream ss;
		ss << var;
		return ss.str();
	}

	/*
	* enum SHELL_COLOR
	* Enumeration used for specifying shell color for 'set_shell_solor'.
	*/
	enum shell_color : int {
		SHELL_GREY = 90,
		SHELL_RED = 91,
		SHELL_BLACK = 92,
		SHELL_YELLOW = 93,
		SHELL_BLUE = 94,
		SHELL_MAGENTA = 95,
		SHELL_CYAN = 96,
		SHELL_WHITE = 97,
		SHELL_GREEN = 32,

		SHELL_BG_GREY = 100, // Background color
		SHELL_BG_RED = 101,
		SHELL_BG_BLACK = 102,
		SHELL_BG_YELLOW = 103,
		SHELL_BG_BLUE = 104,
		SHELL_BG_MAGENTA = 105,

		SHELL_DARK_BLACK = 30,
		SHELL_DARK_RED = 31,
		SHELL_DARK_GREEN = 32,
		SHELL_DARK_YELLOW = 33,
		SHELL_DARK_BLUE = 34,
		SHELL_DARK_MAGENTA = 35,
		SHELL_DARK_CYAN = 36,
		SHELL_DARK_WHITE = 37,

		SHELL_BG_DARK_RED = 41,
		SHELL_BG_DARK_GREEN = 42,
		SHELL_BG_DARK_YELLOW = 43,
		SHELL_BG_DARK_BLUE = 44,
		SHELL_BG_DARK_MAGENTA = 45,
		SHELL_BG_DARK_CYAN = 46,
		SHELL_BG_DARK_WHITE = 47,

		SHELL_RESET = 0,
		SHELL_UNDERLINE = 4,
		SHELL_SELECTED = 7
	};

	/*
	* set_shell_color(enum SHELL_COLOR color)
	* Change the shell's character color using escape codes.
	*/
	inline void set_shell_color(const shell_color& color) {
#if defined(LINUX) || defined(_WINDOWS_SHELL_COLOR)
		std::cout << std::string("\033[" + var_to_string(color) + "m");
#endif
	}

	/*
	* get_color_string(enum SHELL_COLOR color)
	* Get a string to change shell color.
	*/
	inline std::string get_color_string(const shell_color& color) {
#if defined(LINUX) || defined(_WINDOWS_SHELL_COLOR)
		return "\033[" + var_to_string(color) + "m";
#else
		return "";
#endif
	}

	FUNCALIAS(color, get_color_string); // Function alias for easier usage


	//if using C++11
	template<typename UniqueType, typename ... TypeArgs>
	inline std::unique_ptr<UniqueType> make_unique(TypeArgs&& ... args_fwd) {
		return std::unique_ptr<UniqueType>(new UniqueType(std::forward<TypeArgs>(args_fwd)...));
	}

	template<typename SharedType, typename ... TypeArgs>
	inline std::shared_ptr<SharedType> make_shared(TypeArgs&& ... args_fwd) {
		return std::shared_ptr<SharedType>(new SharedType(std::forward<TypeArgs>(args_fwd)...));
	}

	template<typename WeakType, typename ... TypeArgs>
	inline std::weak_ptr<WeakType> make_weak(TypeArgs&& ... args_fwd) {
		return std::weak_ptr<WeakType>(new WeakType(std::forward<TypeArgs>(args_fwd)...));
	}

	/*
	* std::string get_exe_path()
	* Returns the path to the program's binary.
	* Uses the lower level 'get_exe_path_' from 'native.h'.
	*/
	std::string get_exe_path();

	/*
	* std::string get_help_string()
	* Returns "-help Get help for this program."
	* Used for unified help information.
	*/
	inline const std::string get_help_string() {

		return "-help Get help for this program.";
	}

	/*
	* std::string to_unix_slash(std::string s)
	* Turns Windows slashes into Unix-style slashes and returns the string.
	* e.g. to_unix_slash("\folder\folder\file.dat")
	* returns: "/folder/folder/file.dat"
	*/
	std::string to_unix_slash(const std::string& s);

	/*
	* println(...)
	* Prints the data followed by a newline.
	*/
	inline void println() {
		std::cout << std::endl;
	}

	template<typename First, typename ... Many>
	inline void println(const First& arg, const Many&... rest) {
		std::cout << arg;
		println(rest...);
	}

	/*
	* print(...)
	* Prints the data.
	*/
	inline void print() {
		// Template last expansion.
	}

	template<typename First, typename ... Many>
	inline void print(const First& arg, const Many&... rest) {
		std::cout << arg;
		print(rest...);
	}

	/*
	* printerrln(...)
	* Prints the data to err followed by a newline.
	*/
	inline void printerrln() {
		std::cerr << std::endl;
	}

	template<typename First, typename ... Many>
	inline void printerrln(const First& arg, const Many&... rest) {
		std::cerr << arg;
		println(rest...);
	}

	/*
	* printerr(...)
	* Prints the data to err.
	*/
	inline void printerr() {
		// Template last expansion.
	}

	template<typename First, typename ... Many>
	inline void printerr(const First& arg, const Many&... rest) {
		std::cerr << arg;
		print(rest...);
	}

	/*
	* ferror(std::string message, int code)
	* Fatal error: Output an error message (colored in red) and exit with <code> exit value.
	*/
	inline void ferror(std::string message, int code) {
		println(color(SHELL_RED), message, color(SHELL_RESET));
		exit(code);
	}

	/*
	* log(std::string message)
	* Output a log message colored in yellow.
	*/
	inline void log() {
		std::cout << std::endl;
		set_shell_color(SHELL_RESET);
	}

	template<typename First, typename ... Many>
	inline void log(const First& arg, const Many&... rest) {
		set_shell_color(SHELL_YELLOW);
		std::cout << arg;
		log(rest...);
	}

	/*
	* print_logo()
	* Prints Erebos' logo.
	*/
	inline void print_logo() {
		println(""); // TO-DO
	}

	/*
	* bool get_prompt_answer(std::string message, std::string error_message = "", std::string yes_or_no_str = " [Y/n] ", bool exit_on_error = true)
	* Prompt the user [message] and [yes_or_not], returns 'true' if the user answers 'Y' or 'y', 'false' if the user answers 'N' or 'n',
	* returns 'false' or exits (based on [exit_on_error]) if given malformed input.
	* e.g. get_prompt_answer("Are you ok?")
	* > Are you ok? [Y/n]  Y
	* returns: true
	*/
	bool get_prompt_answer(const std::string& message, const std::string& error_message = "", const bool& exit_on_error = true);

	/*
	* std::string parse_quotes(std::string s)
	* Reads and returns a quoted string.
	* e.g. parse_quotes("'Hello man!'")
	* returns: "Hello man!"
	*/
	std::string parse_quotes(const std::string& s);

	/*
	* parse_arg(std::string input, std::vector<std::string>& output)
	* Splits the given string based on spaces and quotes and appends each string to 'output'.
	*/
	void parse_arg(const std::string& input, std::vector<std::string>& output);
}

#endif
