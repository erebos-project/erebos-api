/*
* native.h
* Functions interfacing with the operative system.
* Includes operative system's API.
* All functions are cross-platform, using #ifdefs
* OS-specific functions are followed by '_x' for Linux and '_w' for Windows.
*/

#ifndef _NATIVE_H
#define _NATIVE_H

#include "platform_defs.h"

#include <vector>
#include <string>

namespace erebos {

	namespace native {

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
			int get_pid_by_name(const std::string& name);

			/*
			* int get_pid_by_win_name(std::string win_name)
			* Returns the pid of the process with the specified window name.
			* If the process couldn't be found it returns -1.
			* Windows only.
			*/
#if defined(WINDOWS)
			int get_pid_by_win_name_w(const std::string& win_name);
#endif
			/*
			* bool kill(int pid)
			* Kill the specified process.
			* Returns 'true' if successful, 'false' otherwise.
			*/
			bool kill(const int& pid);

			/*
			* size_t mem_read(unsigned int pid, size_t address, char* result, size_t size = 1)
			* Reads [size] bytes from the specified address from the specified process and writes to result.
			* Returns the amount of bytes read.
			*/
			size_t mem_read(const std::uint32_t pid, const size_t& address, char* result, const size_t& size = 1);

			/*
			* size_t mem_write(unsigned int pid, size_t address, char* data, size_t size = 1)
			* This function writes [size] bytes to the specified address from the specified process.
			* Returns the count of written bytes.
			*/
			size_t mem_write(const std::uint32_t& pid, const size_t& address, char* data, const size_t& size = 1);

			/*
			* bool mem_lock(void* address, size_t size)
			* Locks the specified memory area.
			* Returns 'true' if successful, 'false' otherwise.
			*/
			bool mem_lock(void* address, const size_t& size);

			/*
			* bool mem_unlock(void* address, size_t size)
			* Unlocks the specified memory area.
			* Returns 'true' if successful, 'false' otherwise.
			*/
			bool mem_unlock(void* address, const size_t& size);
		}

		namespace file {

			/*
			* get_dir_file_list(std::string dir, std::vector<std::string>& output)
			* Opens the given directory and appends its files filename's to [output].
			* Returns 'true' if successful, 'false' otherwise.
			*/
			bool get_dir_file_list(const std::string& dir, std::vector<std::string>& output);

			/*
			* get_dir_folder_list(std::string dir, std::vector<std::string>& output)
			* Opens the given directory and appends its folder names to [output].
			* Returns 'true' if successful, 'false' otherwise.
			*/
			bool get_dir_folder_list(const std::string& dir, std::vector<std::string>& output);

			/*
			* bool get_folder_exists(std::string foldername)
			* Checks whether the specified folder exists.
			*/
			bool get_folder_exists(const std::string& foldername);

			/*
			* unsigned long int get_size(std::string filename)
			* Returns the file's size.
			*/
			std::uint32_t get_size(const std::string& filename);

		}

		/*!
		 * @fn erebos::cmd
		 * @param command
		 * @param [out] retval
		 * @return An integer meaning pipe result: 0 OK, -1 Popen failure, -2 Pclose failure
		 * @brief Runs command via an opened pipe
		 */
		int cmd(const std::string& command, int& retval);

		/*!
		 * @fn erebos::cmd
		 * @param command
		 * @param [out] all
		 * @param [out] retval
		 * @return An integer meaning pipe result: 0 OK, -1 Popen failure, -2 Pclose failure
		 * @brief Runs command via an opened pipe
		 */
		int cmd(const std::string& command, std::string& all, int& retval);

		/*!
		 * @fn erebos::is_privileged
		 * @return If user is privileged (Checks for EUID in UNIX/Unix-like environments)
		 * @brief Has user special permissions?
		 */
		bool is_privileged();

		/*!
		 * @fn erebos::get_random_secure
		 * @return Crypto-secure randomized number
		 * @brief Number randomization
		 */
		int get_random_secure();

		//undoc
		std::string get_exe_path_();
	}
}

#endif
