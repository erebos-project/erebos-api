/*!
 * @file file.h
 * @brief file os-independent utilities
 */
#ifndef EREBOS_FILE_H
#define EREBOS_FILE_H

#include "types.h"

namespace erebos {

	/*!
	 * @brief file utilities
	 */
	namespace file {

		/*!
		 * @brief gets full path to s
		 * @param s : relative path
		 * @return full path
		 */
		ERAPI std::string get_path(std::string s);

		/*!
		 * @brief filename extension
		 * @param filename
		 * @return filename extension
		 */
		ERAPI std::string get_extension(const std::string& filename);

		/*!
		 * @brief file name, with extension
		 * @param absolute path
		 * @return file name
		 */
		ERAPI std::string get_name(std::string filename);

		/*!
		 * @brief file basename
		 * @param absolute path
		 * @return file basename
		 */
		ERAPI std::string get_basename(std::string filename);

		/*!
		 * @brief does file exist?
		 * @param filename
		 * @return true if file exists, false otherwise
		 */
		ERAPI bool get_exists(const std::string &filename);

		/*!
		 * @brief read an entire file
		 * @param filename
		 * @return content, if empty string, probably failure
		 */
		ERAPI std::string read(const std::string &filename);

		/*!
		 * @brief read an entire binary file, then store result in holding
		 * erebos::data_t class
		 * @param filename
		 * @param [out]bytecount : how many read bytes? nullptr if not interested (set by default)
		 * @return an erebos::Data structure holding binary data
		 */
		ERAPI Data read_bin(const std::string &filename, std::uint64_t *bytecount = nullptr);

		/*!
		 * @brief write bytes to a file
		 * @param filename
		 * @param data
		 * @param truncate : true by default
		 * @return true if function succeed, false otherwise
		 */
		ERAPI bool write(const std::string &filename, const std::string &data, bool truncate = true);

		/*!
		 * @brief write data hold by erebos::data_t class to binary file
		 * @param filename
		 * @param data : erebos::Data class holding data
		 * @param truncate : true by default
		 * @return true if function succeed, false otherwise
		 */
		ERAPI bool write_bin(const std::string &filename, const Data &data, bool truncate = true);
	}
}

#endif
