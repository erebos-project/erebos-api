/*
* native.h
* Functions interfacing with the operative system.
* Includes operative system's API.
* All functions are cross-platform, using #ifdefs
* OS-specific functions are followed by '_x' for Linux and '_w' for Windows.
*/

#ifndef _NATIVE_H
#define _NATIVE_H
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>

#include "stringutils.h"


namespace erebos {

	/*
	* std::string get_exe_path_()
	* Get the binary file path, including the filename.
	* Used by 'get_exe_path'.
	*/
	std::string get_exe_path_();


	namespace proc {

		/*
		* int get_pid()
		* Returns the calling process' PID.
		*/
		int get_pid();

		/*
		* int get_pid_by_name (std::string win_name)
		* Returns the pid of the process with the specified name.
		* If the process couldn't be found it returns -1.
		*/
		int get_pid_by_name(std::string name);

		/*
		* int get_pid_by_win_name(std::string win_name)
		* Returns the pid of the process with the specified window name.
		* If the process couldn't be found it returns -1.
		* Windows only.
		*/
		int get_pid_by_win_name_w(std::string win_name);

		/*
		* bool kill(int pid)
		* Kill the specified process.
		* Returns 'true' if successful, 'false' otherwise.
		*/
		bool kill(int pid);

		/*
		* size_t mem_read(unsigned int pid, size_t address, char* result, size_t size = 1)
		* Reads [size] bytes from the specified address from the specified process and writes to result.
		* Returns the amount of bytes read.
		*/
		size_t mem_read(unsigned int pid, size_t address, char* result, size_t size = 1);

		/*
		* size_t mem_write(unsigned int pid, size_t address, char* data, size_t size = 1)
		* This function writes [size] bytes to the specified address from the specified process.
		* Returns the count of written bytes.
		*/
		size_t mem_write(unsigned int pid, size_t address, char* data, size_t size = 1);

		/*
		* bool mem_lock(void* address, size_t size)
		* Locks the specified memory area.
		* Returns 'true' if successful, 'false' otherwise.
		*/
		bool mem_lock(void* address, size_t size);

		/*
		* bool mem_unlock(void* address, size_t size)
		* Unlocks the specified memory area.
		* Returns 'true' if successful, 'false' otherwise.
		*/
		bool mem_unlock(void* address, size_t size);

		/*
		* int fork_bg()
		*/
		// int fork_bg()

	}

	/*
	* bool is_privileged()
	* Check if the current process has root access.
	* Returns 'true' if so, 'false' otherwise.
	*/
	bool is_privileged();

	/*
	* int get_random_secure()
	* Returns a cryptographically secure random number.
	*/
	int get_random_secure();


	namespace file {

		/*
		* get_dir_file_list(std::string dir, std::vector<std::string>& output)
		* Opens the given directory and appends its files filename's to [output].
		* Returns 'true' if successful, 'false' otherwise.
		*/
		bool get_dir_file_list(std::string dir, std::vector<std::string>& output);

		/*
		* get_dir_folder_list(std::string dir, std::vector<std::string>& output)
		* Opens the given directory and appends its folder names to [output].
		* Returns 'true' if successful, 'false' otherwise.
		*/
		bool get_dir_folder_list(std::string dir, std::vector<std::string>& output);

		/*
		* bool get_folder_exists(std::string foldername)
		* Checks whether the specified folder exists.
		*/
		bool get_folder_exists(std::string foldername);

		/*
		* unsigned long int get_size(std::string filename)
		* Returns the file's size.
		*/
		unsigned long int get_size(std::string filename);

	}

	/*
	* int cmd_get_output(const std::string& command, std::string& output)
	* Puts into output the entire command output result.
	*/
	int cmd_get_output(const std::string& command, std::string& output);

	/*
	#ifdef LINUX
	void cmd_get_fd(const std::string& command, FILE* rc_fd, const bool &should_check_fd = true);
	#endif
	*/

}

#endif
