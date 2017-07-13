/*!
 * @file framework.h
 * @brief core framework header
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

#include "version.h"
#include "native.h"
#include "file.h"
#include "stringutils.h"

/*!
 * @brief define your own program version
 * (expands to 3 constexpr integers)
 * @param MAJOR (constexpr int VERSION_MAJOR)
 * @param MINOR (constexpr int VERSION_MINOR)
 * @param PATCH (constexpr int VERSION_PATCH)
 * @example DEFVERSION(0, 0, 1);
 */
#define DEFVERSION(MAJOR, MINOR, PATCH) \
	constexpr int VERSION_MAJOR = MAJOR; \
	constexpr int VERSION_MINOR = MINOR; \
	constexpr int VERSION_PATCH = PATCH

/*!
 * @brief this macro allows you to define a new name
 * for your subroutines, no more overhead.
 * Widely used within the framework itself
 * (expands to a constexpr compiletime-type-deducted symbol)
 * WARNING: Does not work with templated functions.
 * @param NEWNAME
 * @param OLDNAME
 */
#define FUNCALIAS(NEWNAME, OLDNAME) \
	constexpr auto NEWNAME = OLDNAME

/*!
 * @brief checks if program cmdline contains -version
 * then prints out the following:
 *   ${PROGAM_NAME} ${PROGRAM_VERSION}
 * At the end, exits resulting in success.
 * WARNING: DEFVERSION() should expand first
 * @param _args: erebos::Args class instance
 * @param progname: program name
 */
#define VERSIONFUNC(_args, progname) \
	if(_args.contains_s("-version")) { \
		std::stringstream ss; \
		ss << "\n" << progname << "\t" << "v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH; \
		std::cout << ss.str() << std::endl; \
		exit(0); \
	}

/*!
 * @brief (pre-c++17)
 * @param xparam
 */
#define SUPPRESS_UNUSED(xparam) \
	((void) xparam)

/*!
 * @brief main erebos namespace
 */
namespace erebos {
	/*!
	 * @brief Erebos API version
	 * @return Erebos API version in the form:
	 * ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
	 */
	inline std::string get_api_version() {
		std::stringstream ss;
		ss << API_VERSION_MAJOR << "." << API_VERSION_MINOR << "." << API_VERSION_PATCH;
		return ss.str();
	}

	/*!
	 * @brief hex from string to int
	 * @param str: a string containing hex value
	 * @return the hex value as integer
	 */
	inline int hex_to_int(const std::string &str) {
		int res;
		std::stringstream ss(str);
		ss >> std::hex >> res;
		return res;
	}

	/*!
	 * @brief converts whatever type to string
	 * @tparam T
	 * @param var: parameter to be converted
	 * @return new string with converted var
	 */
	template<typename T>
	inline std::string var_to_string(const T &var) {
		std::stringstream ss;
		ss << var;
		return ss.str();
	}

	/*!
	 * @brief contains colors integer constants
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
		SHELL_RESET_TEXT = 39,
		SHELL_RESET_BACKGROUND = 49,
		SHELL_OVERLINED = 53,
		SHELL_UNDERLINE = 4,
		SHELL_BLINK = 5,
		SHELL_BLINK_RAPID = 6,
		SHELL_SELECTED = 7
	};

	/*!
	 * @param color
	 * @brief changes color by printing out the escape sequence
	 * Note: only if LINUX or _WINDOWS_SHELL_COLOR are actually defined
	 */
	inline void set_shell_color(const shell_color &color) {
#if defined(LINUX) || defined(_WINDOWS_SHELL_COLOR)
		std::cout << std::string("\033[" + var_to_string(color) + "m");
#endif
	}

	/*!
	 * @brief gets entire color escape sequence
	 * @param color
	 * @return escape sequence with color code (erebos::color() is an alias)
	 */
	inline std::string get_color_string(const shell_color &color) {
#if defined(LINUX) || defined(_WINDOWS_SHELL_COLOR)
		return "\033[" + var_to_string(color) + "m";
#else
		return "";
#endif
	}

	/*!
	 * @brief alias for get_color_string
	 */
	FUNCALIAS(color, get_color_string);

	/*!
	 * @brief returns a string with each character colored differently
	 * @param input string
	 * @return
	 */
	inline std::string make_rainbow_string(const std::string& s) {

		std::string res;
		for (std::size_t i = 0; i < s.size(); ++i) {
			char c = s[i];
			if(c > 32)
				res += get_color_string((shell_color) ((i % 8) + 90));
			res += c;
		}

		res += get_color_string(SHELL_RESET);

		return res;
	}


	/*!
	 * @tparam UniqueType : the type for unique_ptr
	 * @tparam TypeArgs : type for passed parameter to the pointer which unique_ptr will hold
	 * @param args_fwd : parameter to be passed to the pointer which unique_ptr will hold
	 * @return new std::unique_ptr<UniqueType> instance
	 * @brief simple implementation if you're not using C++14 or later
	 */
	template<typename UniqueType, typename ... TypeArgs>
	inline std::unique_ptr<UniqueType> make_unique(TypeArgs &&... args_fwd) {
		return std::unique_ptr<UniqueType>(new UniqueType(std::forward<TypeArgs>(args_fwd)...));
	}

	/*!
	 * @tparam SharedType : the type for shared_ptr
	 * @tparam TypeArgs : type for passed parameter to the pointer which shared_ptr will hold
	 * @param args_fwd : parameter to be passed to the pointer which shared_ptr will hold
	 * @return new std::unique_ptr<SharedType> instance
	 * @brief simple implementation if you're not using C++14 or later
	 */
	template<typename SharedType, typename ... TypeArgs>
	inline std::shared_ptr<SharedType> make_shared(TypeArgs &&... args_fwd) {
		return std::shared_ptr<SharedType>(new SharedType(std::forward<TypeArgs>(args_fwd)...));
	}

	/*!
	 * @tparam WeakType : the type for weak_ptr
	 * @tparam TypeArgs : type for passed parameter to the pointer which weak_ptr will hold
	 * @param args_fwd : parameter to be passed to the pointer which weak_ptr will hold
	 * @return new std::weak_ptr<WeakType> instance
	 * @brief simple implementation if you're not using C++14 or later
	 */
	template<typename WeakType, typename ... TypeArgs>
	inline std::weak_ptr<WeakType> make_weak(TypeArgs &&... args_fwd) {
		return std::weak_ptr<WeakType>(new WeakType(std::forward<TypeArgs>(args_fwd)...));
	}

	/*!
	 * @brief gets program executable
	 * @return program executable string
	 */
	std::string get_exe_path();

	/*!
	 * @return "-help Get help for this program."
	 */
	inline const std::string get_help_string() {

		return "-help Get help for this program.";
	}

	/*!
	 * @brief converts backslash to slash
	 * @param s : windows-like path
	 * @return new string containing unix-like path
	 */
	std::string to_unix_slash(const std::string &s);

	/*!
	 * @brief prints newline
	 */
	inline void println() {
		std::cout << '\n';
	}

	/*!
	 * @tparam First
	 * @tparam Many
	 * @param arg
	 * @param rest
	 * @brief Prints as many argument as specified, then newline
	 */
	template<typename First, typename ... Many>
	inline void println(const First &arg, const Many &... rest) {
		std::cout << arg;
		println(rest...);
	}

	/*!
	 * @brief Does nothing. Literally
	 */
	inline void print() {
		// Template last expansion.
	}

	/*!
	 * @tparam First
	 * @tparam Many
	 * @param arg
	 * @param rest
	 * @brief Prints as many arguments as specified, no newline at the end
	 */
	template<typename First, typename ... Many>
	inline void print(const First &arg, const Many &... rest) {
		std::cout << arg;
		print(rest...);
	}

	/*!
	 * @brief prints a newline to stderr
	 */
	inline void printerrln() {
		std::cerr << '\n';
	}

	/*!
	 * @tparam First
	 * @tparam Many
	 * @param arg
	 * @param rest
	 * @brief prints to stderr as many argument as specified, newline at the end
	 */
	template<typename First, typename ... Many>
	inline void printerrln(const First &arg, const Many &... rest) {
		std::cerr << arg;
		println(rest...);
	}

	/*!
	 * @brief Does nothing. Literally
	 */
	inline void printerr() {
		// Template last expansion.
	}

	/*!
	 * @tparam First
	 * @tparam Many
	 * @param arg
	 * @param rest
	 * @brief prints to stderr as many argument as specified, no newline at the end
	 */
	template<typename First, typename ... Many>
	inline void printerr(const First &arg, const Many &... rest) {
		std::cerr << arg;
		print(rest...);
	}

	/*!
	 * @param message : message to be printed out
	 * @param code : exit code, -1 by default
	 * @brief prints out to stderr your message, then exits with 'code'
	 */
	inline void ferror(const std::string &message, const int &code = -1) {
		printerrln(color(SHELL_RED), message, color(SHELL_RESET));
		exit(code);
	}

	/*!
	 * @brief Prints erebos logo
	 */
	inline void print_logo() {
		println(color(SHELL_BLUE),
				"                       .-/+oossso+/-\n"
				"                   `:ohmNMMMMMMMMMMMMNds:\n"
				"                 `/yNMMmdyso+/////+shmMMMMm.\n"
				"               '+mMms`             `-sdms`\n"
				"             `hMh:`                    ``\n"
				"            -sMy`\n"
				"            dM:\n"
				"           +Mhs`\n"
				"            +mmo:/syhhhhh`..\n"
				"           .+NNdNMNhyssssymMmMm.\n"
				"           .smdommM-/++oo++/`\n"
				"         `+Nd/`\n"
				"        `yMs`\n"
				"         sMs\n"
				"        `NMn.\n"
				"        `MMm:                        :/\n"
				"         sMm:`                    .sNs\n"
				"         `yMMdo-``.         .``-/ymm/\n"
				"           :hNMMNmdhyyyyyyyhdmNMNh/`\n"
				"             .+ymNNMMMMMMMNNmho:`\n"
				"                  `.-::/::-.`\n",
				color(SHELL_RESET)
			);
	}

	/*!
	 * @brief prompt menu facility
	 * @param message : your question
	 * @param error_message : error message if user answers wrong (default = "")
	 * @param exit_on_error : should exit on wrong input by user? (default = true)
	 * @return user chosen Y or N ?
	 */
	bool get_prompt_answer(const std::string &message, const std::string &error_message = "",
						   const bool &exit_on_error = true);

	/*!
	 * @brief new quoted string
	 * @param s : string to be quoted
	 * @return new quoted string
	 */
	std::string parse_quotes(const std::string &s);

	/*!
	 * @brief argument parser, used by erebos::Args
	 * @param input : input string to be parsed (based on spaces and quotes)
	 * @param output : parsed string
	 */
	void parse_arg(const std::string &input, std::vector<std::string> &output);
}

#endif
