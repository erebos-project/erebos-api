#ifndef _FTYPES_H
#define _FTYPES_H

#include <vector>
#include <string>
#include <cstring>

namespace erebos {

	void parse_arg(const std::string& input, std::vector<std::string>& output);

	/*
	* Args
	* A class for terminal argument handling.
	* Construct with Args(argc, argv).
	* Commonly declared and used in Erebos as 'args'.
	*/
	class Args {
		private:
			std::vector<std::string> list;
			size_t argsize;

		public:
			inline Args(const int& argc, char const *argv[]) {
				std::string s;
				for (int i = 0; i < argc; ++i)
					s += std::string(argv[i]) + ' ';

				if(argc)
					parse_arg(s, list);

				argsize = list.size();
			}

			/*
			* std::string operator[](size_t i)
			* Get the nth argument.
			*/
			inline std::string operator[](const size_t& i) {
				if(list.size() > i) 
					return list[i];

				return "";
			}

			/*
			* bool contains(std::string s)
			* Checks whether the argument list contains the specified string.
			*/
			inline bool contains(const std::string& s) {
				for (size_t i = 0; i < argsize; ++i)
					if(list[i] == s) 
						return true;
				return false;
			}

			/*
			* bool contains_s(std::string s)
			* Checks wether the argument list contains the specified string or its first two characters.
			*/
			inline bool contains_s(const std::string& s) {

				for (size_t i = 0; i < argsize; ++i)
					if(list[i] == s) 
						return true;

				std::string s2;
				s2 += s[0];
				s2 += s[1];

				for (size_t i = 0; i < argsize; ++i)
					if(list[i] == s2) 
						return true;

				std::string s3 = std::string("-") + s;

				for (size_t i = 0; i < argsize; ++i)
					if(list[i] == s3) 
						return true;


				return false;
			}

			/*
			* size_t size()
			* Get the argument list size.
			*/
			inline size_t size() {
				return argsize;
			}
	};
	
	class data_t {
		using data_size = unsigned long;

		public:
			char* data;
			data_size size;

			inline data_t() : data(nullptr), size(0) {}

			inline explicit data_t(const std::string& str) 
					: data(const_cast<char*>(str.c_str())), 
						size(static_cast<data_size>(str.size())) {
				this->data = new char[size];
				memcpy(this->data, str.c_str(), size);
			}

			inline data_t(const char* data, const data_size& size) 
					: size(size) {
				this->data = new char[size];
				memcpy(this->data, data, size);
			}

			inline void free() {
				delete[] data;
				size = 0;
			}

			inline char operator[](const data_size& index) {
				return data[index];
			}
	};

}

#endif
