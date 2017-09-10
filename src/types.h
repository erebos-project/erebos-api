/*!
 * @file types.h
 * @brief framework core data types
 */
#ifndef EREBOS_TYPES_H
#define EREBOS_TYPES_H

#include <vector>
#include <string>

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
}

#endif
