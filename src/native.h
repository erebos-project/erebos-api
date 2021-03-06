/*!
 * @file native.h
 * @brief functions implemented using native APIs
 */
#ifndef _NATIVE_H
#define _NATIVE_H

#include "platform_defs.h"

#include <string>
#include <vector>

namespace erebos {

	/*!
	 * @brief process utilities namespace
	 */
	namespace proc {

		/*!
		 * @brief get this process' PID
		 * @return process' PID
		 */
		ERAPI int get_pid();

		/*!
		 * @brief look for process' name and retrieve PIDs
		 * @param name : process names
		 * @param [out]output : PIDs
		 * @return 0 if success, < 0 otherwise
		 */
		ERAPI int get_pid_by_name(const std::string &name, std::vector<int> &output);

#if defined(LINUX)
		constexpr auto pidof = get_pid_by_name;
#endif

#if defined(WINDOWS)
		/*!
		 * @brief gets PID by window name (Windows only)
		 * @param win_name: window name
		 * @return 0 if success, < 0 otherwise
		 */
		ERAPI int get_pid_by_win_name(const std::string& win_name);
#endif

		/*!
		 * @brief sends a TERM signal to PID process
		 * @param pid : target pid
		 * @return true if PID was successfully killed
		 */
		ERAPI bool kill(const int &pid);

		/*!
		 * @brief read a chunk of bytes from process' address space
		 * @param pid : target PID
		 * @param address : target address
		 * @param [out]result : read bytes
		 * @param size : (set to 1 by default) bytes to be read
		 * @return read bytes from address
		 */
		ERAPI int mem_read(const int &pid, const size_t &address, char *result, const size_t &size = 1);

		/*!
		 * @brief write a chunk of bytes to process' address space
		 * @param pid : target PID
		 * @param address : target address
		 * @param data : bytes to be written
		 * @param size : (set to 1 by default) how any bytes
		 * @return written bytes to address
		 */
		ERAPI int mem_write(const int &pid, const size_t &address, char *data, const size_t &size = 1);

		/*!
		 * @brief locks the specified memory area
		 * @param address : target start address
		 * @param size : bytes
		 * @return true if memory could be locked, false otherwise
		 */
		ERAPI bool mem_lock(void *address, const size_t &size);

		/*!
		 * @brief unlocks the specified memory area (previously locked)
		 * @param address : target start address
		 * @param size : bytes
		 * @return true if memory could be unlocked, false otherwise
		 */
		ERAPI bool mem_unlock(void *address, const size_t &size);
	}


	namespace file {

		/*!
		 * @brief retrieve directory file list
		 * @param dir : directory target
		 * @param [out]output : file list
		 * @return true if everything went fine, false otherwise
		 */
		ERAPI bool get_dir_file_list(const std::string &dir, std::vector<std::string> &output);

		/*!
		 * @brief retrieve directory folder list
		 * @param dir : directory target
		 * @param [out]output : dir list
		 * @return true if everything went fine, false otherwise
		 */
		ERAPI bool get_dir_folder_list(const std::string &dir, std::vector<std::string> &output);

		/*!
		 * @brief checks if folder exist
		 * @param foldername : directory target
		 * @return true if exists, false otherwise
		 */
		ERAPI bool get_folder_exists(const std::string &foldername);

		/*!
		 * @brief get file size
		 * @param filename : your file
		 * @return file bytes, less than 0 if function fails
		 */
		ERAPI int get_size(const std::string &filename);

#if defined(LINUX)

		/*!
		 * @brief get filename by link
		 * @param filename : a symbolic link
		 * @return the correspondent file to the symlink
		 */
		std::string readlink(const std::string &filename);

#endif

		/*!
		 * @brief remove a file
		 * @param filename : your filename
		 * @return true if function succeed, false otherwise
		 */
		ERAPI bool remove(const std::string &filename);

		/*!
		 * @brief remove a directory
		 * @param dirname : your directory
		 * @return true if function succeed, false otherwise
		 */
		ERAPI bool remove_dir(const std::string &dirname);

	}

	/*!
	 * @param command
	 * @param [out] retval
	 * @return The result of the pipe usage: 0 if successful, -1 if popen failed, -2 if pclose failed
	 * @brief Executes a command and writes the exit code to [retval]
	 */
	ERAPI int pipe_open(const std::string &command, int *retval = nullptr);

	/*!
	 * @param command
	 * @param [out] output
	 * @param [out] retval
	 * @return The result of the pipe usage: 0 if successful, -1 if popen failed, -2 if pclose failed
	 * @brief Executes a command and writes the output to [output] and the exit code to [retval]
	 */
	ERAPI int pipe_open(const std::string &command, std::string &output, int *retval = nullptr);

	/*!
	 * @return The Current Working Directory
	 * @brief Returns the Current Working Directory
	 */
	ERAPI std::string get_cwd();

	/*!
	 * @return On success returns true, false otherwise
	 * @brief Sets the Current Working Directory
	 */
	ERAPI bool set_cwd(std::string path);

	/*!
	 * @return If user is privileged (Checks for EUID in UNIX/Unix-like environments)
	 * @brief Has user special permissions?
	 */
	ERAPI bool is_privileged();

	/*!
	 * @return Crypto-secure randomized number
	 * @brief Number randomization
	 */
	ERAPI int get_random_secure();

	/*!
	 * @return String error from errno integer
	 * @param errn : the errno integer
	 */
	ERAPI std::string string_from_errno(const int &errn);

	//undoc
	ERAPI std::string _get_exe_path_();

}

#endif
