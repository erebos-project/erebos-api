/*
* framework.h
* Erebos API providing common utility functions.
* Includes 'native.h' and 'stringutils.h'
* All functions should be cross-platform.
*/

#ifndef _FRAMEWORK_H
#define _FRAMEWORK_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>

#include "native.h"
#include "ftypes.h"
#include "version.h"

/*
* DEFVERSION(int MAJOR, int MINOR, int PATCH) macro for defining a program's version easily.
* e.g. DEFVERSION(1, 0, 0)
*/
#define DEFVERSION(MAJOR, MINOR, PATCH) constexpr int VERSION_MAJOR = MAJOR; \
										constexpr int VERSION_MINOR = MINOR; \
										constexpr int VERSION_PATCH = PATCH;

#define FUNCALIAS(NEWNAME, OLDNAME) constexpr auto NEWNAME = OLDNAME;

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
#define VERSIONFUNC(progname) if(args.contains_s("-version")) { \
_print_version_exit(progname, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);}


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
	* _print_version_exit(const char* progname, int VERSION_MAJOR, int VERSION_MINOR, int VERSION_PATCH)
	* Function used by VERSIONFUNC, not intended for other uses.
	*/
	inline void _print_version_exit(const char* progname, int VERSION_MAJOR,
									int VERSION_MINOR, int VERSION_PATCH) {
		std::stringstream ss;
		ss << "\n" << progname << "\t" << "v" << VERSION_MAJOR << "."
		<< VERSION_MINOR << "." << VERSION_PATCH;
		std::cout << ss.str() << std::endl;
		exit(0);
	}

	/*
	* int hex_to_int(std::string str)
	* Converts the specified hex-like string to int.
	*/
	inline int hex_to_int(std::string str) {
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
	inline std::string var_to_string(T var) {
		std::stringstream ss;
		ss << var;
		return ss.str();
	}

	/*
	* enum SHELL_COLOR
	* Enumeration used for specifying shell color for 'set_shell_solor'.
	*/
	typedef enum : int {
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
	} SHELL_COLOR;

	/*
	* set_shell_color(enum SHELL_COLOR color)
	* Change the shell's character color using escape codes.
	*/
	inline void set_shell_color(SHELL_COLOR color) {

#if defined(LINUX) | defined(_WINDOWS_SHELL_COLOR)
		std::cout << std::string("\033[" + var_to_string((int) color) + "m");
#endif

	}

	/*
	* get_color_string(enum SHELL_COLOR color)
	* Get a string to change shell color.
	*/
	inline std::string get_color_string(SHELL_COLOR color) {

#if defined(LINUX) | defined(_WINDOWS_SHELL_COLOR)
		return std::string("\033[" + var_to_string((int) color) + "m");
#endif
	}

	FUNCALIAS(colstr, get_color_string) // Function alias for easier usage
	
	/*
	* std::string get_exe_path()
	* Returns the path to the program's binary.
	* Uses the lower level 'get_exe_path_' from 'native.h'.
	*/
	std::string get_exe_path();

	FUNCALIAS(get_erebos_folder, get_exe_path);

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
	std::string to_unix_slash(std::string s);

	namespace file {

		/*
		* std::string get_file_path(std::string filename)
		* Parses the given string and returns the path without the filename.
		* Windows slash is converted to unix-style slash using 'to_unix_slash'
		* If the path couldn't be found returns an empty string.
		* e.g. get_file_path("/folder/folder/file")
		* returns: "/folder/folder/"
		*/
		std::string get_path(std::string s);

		/*
		* std::string get_file_extension(std::string filename)
		* Parses the given filename and returns the file's extension.
		* e.g. get_file_extension("file.dat")
		* returns: "dat"
		* Does not consider multiple extension files, in the case returns the last extension.
		* e.g. get_file_extension("file.tar.bz")
		* returns: "bz"
		*/
		std::string get_extension(std::string filename);

		/*
		* std::string get_file_name(std::string filename)
		* Parses the given filename and returns the file's name without the path.
		* e.g. get_file_name("/folder/file.dat")
		* returns: "file.dat"
		*/
		std::string get_name(std::string filename);

		/*
		* std::string get_basename(std::string filename)
		* Parses the given filename and returns the file's basename.
		* e.g. get_file_basename("/folder/file.dat")
		* returns: "file"
		*/
		std::string get_basename(std::string filename);

		/*
		* bool get_exists(std::string filename)
		* Checks wether the file exists or not.
		*/
		bool get_exists(std::string filename);

		/*
		* std::string read(std::string filename)
		* Reads the whole content of a file into a string.
		*/
		std::string read(std::string filename);

		/*
		* data_t read_bin(std::string filename)
		* Reads the whole file content into a string as binary data.
		* Returns an empty data_t structure on fail.
		*/
		data_t read_bin(std::string filename, unsigned long long* bytecount = nullptr);


		/*
		* bool write(std::string filename, std::string data, bool truncate)
		* Writes the given string to the specified file.
		* Returns 'true' if the file could be written, false otherwise.
		*/
		bool write(std::string filename, std::string data, bool truncate = true);

		/*
		* bool write_bin(std::string filename, data_t data, bool truncate)
		* Writes the given data to the specified file as binary data.
		* Returns 'true' if successful, 'false' otherwise.
		*/
		bool write_bin(std::string filename, data_t data, bool truncate = true);
		
		/*
		* remove(std::string filename)
		* Deletes the specified file, cross-platform way.
		*/
		bool remove(std::string filename);

	}

	/*
	* println(...)
	* Prints the data followed by a newline.
	*/
	inline void println() {
		std::cout << std::endl;
	}

	template<typename first, typename ... many>
	inline void println(first arg, const many&... rest) {
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

	template<typename first, typename ... many>
	inline void print(first arg, const many&... rest) {
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

	template<typename first, typename ... many>
	inline void printerrln(first arg, const many&... rest) {
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
	
	template<typename first, typename ... many>
	inline void printerr(first arg, const many&... rest) {
		std::cerr << arg;
		print(rest...);
	}

	/*
	* ferror(std::string message, int code)
	* Fatal error: Output an error message (colored in red) and exit with <code> exit value.
	*/
	inline void ferror(std::string message, int code) {
		println(colstr(SHELL_RED), message, colstr(SHELL_RESET));
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

	template<typename first, typename ... many>
	inline void log(first arg, const many&... rest) {
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
	* term_clear()
	* Clears the console, cross-platform way.
	*/
	void term_clear();

	/*
	* bool get_prompt_answer(std::string message, std::string error_message = "", std::string yes_or_no_str = " [Y/n] ", bool exit_on_error = true)
	* Prompt the user [message] and [yes_or_not], returns 'true' if the user answers 'Y' or 'y', 'false' if the user answers 'N' or 'n',
	* returns 'false' or exits (based on [exit_on_error]) if given malformed input.
	* e.g. get_prompt_answer("Are you ok?")
	* > Are you ok? [Y/n]  Y
	* returns: true
	*/
	bool get_prompt_answer(std::string message, std::string error_message = "", bool exit_on_error = true);

	/*
	* std::string parse_quotes(std::string s)
	* Reads and returns a quoted string.
	* e.g. parse_quotes("'Hello man!'")
	* returns: "Hello man!"
	*/
	std::string parse_quotes(std::string s);

	/*
	* parse_arg(std::string input, std::vector<std::string>& output)
	* Splits the given string based on spaces and quotes and appends each string to 'output'.
	*/
	void parse_arg(std::string input, std::vector<std::string>& output);

	/*
	 * cmd(const std::string& command)
	 * Temporary solution for executing a shell command,
	 * Not getting output, see cmd_get_output
	 */
	void cmd(const std::string& command);

	struct Time {

		size_t year;
		size_t month;
		size_t day;
		size_t hour;
		size_t min;
		size_t sec;

	};

	/*
	* Time get_localtime()
	* Get the system's time in Time handy structure.
	*/
	Time get_localtime();

}

#endif
