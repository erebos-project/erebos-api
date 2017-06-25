#ifndef _FTYPES_H
#define _FTYPES_H
#include <vector>
#include <string>
#include <string.h>

namespace erebos {

	void parse_arg(std::string input, std::vector<std::string>& output);

	/*
	* Args
	* A class for terminal argument handling.
	* Construct with Args(argc, argv).
	* Commonly declared and used in Erebos as 'args'.
	*/
	class Args {

		private:

			std::vector<std::string> list;

		public:

			inline Args(int argc, char const *argv[]) {

				std::string s;
				for (int i = 0; i < argc; ++i)
					s += std::string(argv[i]) + ' ';

				if(argc)
					parse_arg(s, list);
			}

			/*
			* std::string operator[](size_t i)
			* Get the nth argument.
			*/
			inline std::string operator[](size_t i) {
				if(list.size() > i) return list[i];
				return "";
			}

			/*
			* bool contains(std::string s)
			* Checks wether the argument list contains the specified string.
			*/
			inline bool contains(std::string s) {
				for (int i = 0; i < list.size(); ++i)
					if(list[i] == s) return true;
				return false;
			}

			/*
			* bool contains_s(std::string s)
			* Checks wether the argument list contains the specified string or its first two characters.
			*/
			inline bool contains_s(std::string s) {

				for (int i = 0; i < list.size(); ++i)
					if(list[i] == s) return true;

				std::string s2;
				s2 += s[0];
				s2 += s[1];

				for (int i = 0; i < list.size(); ++i)
					if(list[i] == s2) return true;

				std::string s3 = std::string("-") + s;

				for (int i = 0; i < list.size(); ++i)
					if(list[i] == s3) return true;


				return false;
			}

			/*
			* size_t size()
			* Get the argument list size.
			*/
			inline size_t size() {
				return list.size();
			}

	};
	
	class data_t {

		using data_size = unsigned long int;

		public:

			char* data;
			data_size size;


			inline data_t() : data(nullptr), size(0) {}

			inline explicit data_t(std::string str) : data((char*) str.c_str()), size(str.size()) {

				this->data = new char[size];
				memcpy(this->data, (char*) &str, size);
			}

			inline data_t(const char* data, data_size size) : size(size) {

				this->data = new char[size];
				memcpy(this->data, data, size);
			}

			inline void free() {
				delete[] data;
				size = 0;
			}

			inline char operator[](data_size index) {
				return data[index];
			}

	};

}

#endif
