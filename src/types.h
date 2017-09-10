/*!
 * @file types.h
 * @brief framework core data types
 */
#ifndef EREBOS_TYPES_H
#define EREBOS_TYPES_H

#include <vector>
#include <string>
#include <cstring>
#include "platform_defs.h"

namespace erebos {

	/*!
	 * @brief This function is used by erebos::Args class and you should not use this
	 * @param input : input string
	 * @param [out] output : output vector containing arguments
	 */
	ERAPI void parse_arg(const std::string &input, std::vector<std::string> &output);


	/*!
	 * @brief command line argument parser
	 */
	class Args {
	private:
		std::vector<std::string> list;
		size_t argsize;

	public:
		/*!
		 * @brief class constructor
		 * @param argc
		 * @param argv
		 */
		inline Args(const int &argc, char *argv[]) :
				list({}), argsize(0) {

			std::string s;
			for (int i = 0; i < argc; ++i)
				s += std::string(argv[i]) + ' ';

			if (argc)
				parse_arg(s, list);

			argsize = list.size();
		}

		/*!
		 * @brief (may throw exception) gets the i-th argument from parsed arguments
		 * @param i
		 * @return i-th argument
		 */
		inline const std::string &operator[](const size_t &i) const {
			return list.at(i);
		}

		/*!
		 * @brief checks if the s-string is available
		 * @param s
		 * @return true if inside, false otherwise
		 */
		inline bool contains(const std::string &s) const {
			for (size_t i = 0; i < argsize; ++i)
				if (list[i] == s)
					return true;
			return false;
		}

		/*!
		 * @brief extended function, checks for shorter versions of the argument
		 * @param s
		 * @return true if s-string is inside, false otherwise
		 */
		inline bool contains_s(const std::string &s) const {

			for (size_t i = 0; i < argsize; ++i)
				if (list[i] == s)
					return true;

			std::string s2;
			s2 += s[0];
			s2 += s.at(1);

			for (size_t i = 0; i < argsize; ++i)
				if (list[i] == s2)
					return true;

			std::string s3 = "-";
			s3 += s;

			for (size_t i = 0; i < argsize; ++i)
				if (list[i] == s3)
					return true;


			return false;
		}


		/*!
		 * @brief retrieve argument length
		 * @return const-ref to argument size
		 */
		inline const size_t &size() const noexcept {
			return argsize;
		}
	};

	class DataException : public std::exception {
	public:
		virtual const char* what() const noexcept;
	};

	/*!
	 * @brief hold generic data (dynamic allocated)
	 */
	class Data {
	public:
		/*!
		 * @brief 64-bit unsigned integer
		 */
		using data_size = unsigned long long;

		/*!
		 * @brief data handled by data_t class
		 */
		char* data;

		/*!
		 * @brief data size
		 */
		data_size size;

		/*!
		 * @brief class constructor, initializes data to nullptr and size to 0
		 */
		inline Data() : data(nullptr), size(0) {}

		/*!
		 * @brief class constructor, dynamically allocates, and makes deep copy of data
		 * @param str
		 */
		inline explicit Data(const std::string &str)
				: size(static_cast<data_size>(str.size())) {
			this->data = new char[size];
			memcpy(this->data, str.c_str(), size);
		}

		/*!
		 * @brief class deconstructor, this ensures data is freed when object goes out-of-scope
		 */
		inline ~Data() {
			free();
		}

		/*!
		 * @brief class constuctor, dynamically allocates, and makes deep copy of data
		 * @param data
		 * @param size
		 */
		inline Data(const char *data, const data_size &size)
				: size(size) {
			this->data = new char[size];
			memcpy(this->data, data, size);
		}

		/*!
		 * @brief class copy-constructor, this allows class copy
		 * @param prev
		 */
		inline Data(const Data &prev) {
			this->data = new char[prev.size];
			this->size = prev.size;
			memcpy(this->data, prev.data, this->size);
		}

		/*!
		 * @brief class move constructor
		 * @param rdata_prev
		 */
		inline Data(Data&& rdata_prev) {
			this->data = new char[rdata_prev.size];
			this->size = rdata_prev.size;
			memcpy(this->data, rdata_prev.data, this->size);
		}

		/*!
		 * @brief copy-assignment operator overload
		 * @param prev
		 */
		inline Data& operator=(const Data &prev) {
			this->data = new char[prev.size];
			this->size = prev.size;
			memcpy(this->data, prev.data,this->size);
			return *this;
		}

		/*!
		 * @brief frees dynamically-allocated region before class gets destroyed.
		 * (Ready for holding other data)
		 * @returns true if correctly freed, false if data is a null pointer
		 */
		inline bool free() {
			if (data) {
				delete[] data;
				size = 0;
				data = nullptr;
				return true;
			}

			return false;
		}

		/*!
		 * @brief comparison operator overload, compares two memory blocks (may throw DataException)
		 * @param other: another data structure holding *SOMETHING*
		 * @return true if equals, false otherwise
		 */
		inline bool operator==(const Data& other) const {

			if(!data || !other.data)
				throw DataException();

			if(size != other.size)
				return false;

			return !memcmp(other.data, data, size);
		}

		/*!
		* @brief comparison operator overload, compares two memory blocks (may throw DataException)
		* @param other: another data structure holding *SOMETHING*
		* @return true if not equal, false otherwise
		*/
		inline bool operator!=(const Data& other) const {

			if(!data || !other.data)
				throw DataException();
			
			if(size != other.size)
				return true;

			return memcmp(other.data, data, size);
		}

	};
}

#endif
