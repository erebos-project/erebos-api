#ifndef EREBOS_FILE_H
#define EREBOS_FILE_H

#include "ftypes.h"

namespace erebos {
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
		std::string get_extension(const std::string& filename);

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
		bool get_exists(const std::string& filename);

		/*
		* std::string read(std::string filename)
		* Reads the whole content of a file into a string.
		*/
		std::string read(const std::string& filename);

		/*
		* data_t read_bin(std::string filename)
		* Reads the whole file content into a string as binary data.
		* Returns an empty data_t structure on fail.
		*/
		data_t read_bin(const std::string& filename, unsigned long long* bytecount = nullptr);


		/*
		* bool write(std::string filename, std::string data, bool truncate)
		* Writes the given string to the specified file.
		* Returns 'true' if the file could be written, false otherwise.
		*/
		bool write(const std::string& filename, const std::string& data, bool truncate = true);

		/*
		* bool write_bin(std::string filename, data_t data, bool truncate)
		* Writes the given data to the specified file as binary data.
		* Returns 'true' if successful, 'false' otherwise.
		*/
		bool write_bin(const std::string& filename, const data_t& data, bool truncate = true);

		/*
		* remove(std::string filename)
		* Deletes the specified file, cross-platform way.
		*/
		bool remove(const std::string& filename);

	}
}

#endif