/*!
 * @file stringutils.h
 * @brief string utilities
 */
#ifndef EREBOS_STRINGUTILS_H
#define EREBOS_STRINGUTILS_H

#include "platform_defs.h"

#include <string>
#include <sstream>
#include <vector>
#include <cstring>

namespace erebos {
	/*!
	 * @brief contains string manipulation utils
	 */
	namespace strutil {

		/*!
		 * @brief defines a 64 bit signed integer
		 */
		using ssize = long long;

		/*!
		 * @brief defines a 32 bit signed integer
		 */
		using ssize32 = long;

		/*!
		 * @brief erase newline at the end of the string
		 * @param [out]target : string to be chomp-ed
		 * @return true if newline was found and erased, false otherwise
		 */
		inline bool chomp(std::string &target) {
			const size_t end_pos = target.size() - 1;

			if (target.at(end_pos) == '\n') {
				target.erase(end_pos);
				return true;
			}

			return false;
		}

		/*!
		 * @brief check if character is literal
		 * @param c
		 * @return true if c is literal, false otherwise
		 */
		inline bool is_literal(const char &c) {
			return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
		}

		/*!
		 * @brief check if character is numeric
		 * @param c
		 * @return true if c is numeric, false otherwise
		 */
		inline bool is_numeral(const char &c) {
			return (c >= '0') && (c <= '9');
		}

		/*!
		 * @brief check if char is double/single quote
		 * @param c
		 * @return true if the char 'c' is a single/double quote, false otherwise
		 */
		inline bool is_quotes(const char &c) {
			return c == '\'' || c == '\"';
		}

		/*!
		 * @brief check if string is literal
		 * @param s
		 * @return true if string is literal, false otherwise
		 */
		inline bool is_literal(const std::string &s) {
			for (size_t i = 0; i < s.size(); ++i) {
				if (!is_literal(s[i]))
					return false;
			}
			return true;
		}

		/*!
		 * @brief check if string is numeric
		 * @param s
		 * @return true if string is numeric, false otherwise
		 */
		inline bool is_numeral(const std::string &s) {
			for (size_t i = 0; i < s.size(); ++i) {
				if (!is_numeral(s[i]))
					return false;
			}
			return true;
		}

		/*!
		 * @brief cut a string
		 * @param s : string to be cutted
		 * @param offset : offset at
		 * @param size : size of the cut
		 * @return new cutted string
		 */
		inline std::string cut(const std::string &s, const size_t &offset, size_t size = 0) {
			std::string res;
			if (!size)
				size = s.size() - offset;

			res.reserve(size);

			for (size_t i = offset; i < offset + size; ++i)
				res += s[i];

			return res;
		}

		/*!
		 * @brief replace substring in string
		 * @param [out]target : string for replacement
		 * @param replaced : substring TO BE replaced
		 * @param replacement : replacement for 'replaced'
		 * @param n : how many times
		 */
		inline void replace(std::string &target, const std::string &replaced,
				const std::string &replacement, const size_t &n = 0) {
			const size_t replaced_length = replaced.length();

#if defined(WINDOWS)
			ssize32 position = -1;
#elif defined(LINUX)
			ssize position = -1;
#endif

			size_t iterations = 0;

			while ((position = target.find(replaced, position + 1)) != std::string::npos) {
				target.replace(position, replaced_length, replacement);
				iterations++;

				if (iterations == n)
					break;
			}
		}

		/*!
		 * @brief replace character in string
		 * @param [out]target : string for replacement
		 * @param replaced : char to be replaced
		 * @param replacement : replacement for 'replaced'
		 * @param n : how many times
		 */
		inline void replace(std::string &target, const char &replaced,
				const char &replacement, const size_t &n = 0) {
			size_t iterations = 0;
			for (size_t i = 0; i < target.size(); ++i) {
				if (target[i] == replaced) {
					target[i] = replacement;
					iterations++;
				}

				if (iterations == n && n > 0)
					break;
			}
		}

		/*!
		 * @brief ruby-style string multiply
		 * @param s : string to be multiplied
		 * @param times : how many times the multiplication has to be repeated
		 * @return new multiplied string
		 */
		inline std::string mul(const std::string &s, const size_t &times) {
			std::string res;
			for (size_t i = 0; i < times; ++i)
				res += s;
			return res;
		}

		/*!
		 * @brief split a string by 'splchr' and put it into 'output' vector
		 * @param str : string to be splitted
		 * @param splchr : split character
		 * @param [out]output : target vector
		 */
		inline void split(const std::string &str, const char &splchr, std::vector<std::string> &output) {

			std::stringstream ss(str);
			std::string item;

			while (getline(ss, item, splchr))
				output.emplace_back(std::move(item));
		}

		/*!
		 * @brief find an element into an array of bytes (should be null-terminated in order to work the right way)
		 * @param raw_array : the array
		 * @param element : the element
		 * @return array index, -1 if not found
		 */
		inline ssize index_of(const char *raw_array, const char &element) {
			for (ssize i = 0; i < static_cast<ssize>(strlen(raw_array)); i++)
				if (raw_array[i] == element)
					return i;

			return -1;
		}

		/*!
		 * @brief find an element into an array of bytes
		 * @param raw_array : the array
		 * @param element : the element
		 * @param len : array length
		 * @return array index, -1 if not found
		 */
		inline ssize index_of(const char *raw_array, const char &element, const ssize &len) {
			for(ssize i = 0; i < len; i++)
				if(raw_array[i] == element)
					return i;

			return -1;
		}

        /*!
         * @brief converts backslash to slash
         * @param s : windows-like path
         * @return new string containing unix-like path
         */
        inline std::string to_unix_slash(const std::string &s) {
            std::string from = s;
            replace(from, '\\', '/');
            return from;
        }

        /*!
         * @brief return the text between two quotes
         * @param s : quoted string
         * @return text between quotes
         */
        inline std::string parse_quotes(const std::string &s) {

            if(s == "")
                return "";

            const char &target = s.at(0);
            if (target != '\"' && target != '\'')
                return s;

            std::string res;

            const size_t size = s.size();
            for (size_t i = 1; i < size; ++i) {
                const char &target = s[i];
                if (target != '\"' && target != '\'')
                    res += target;
                else
                    break;
            }

            return res;
        }

#if defined(LINUX)

		/*!
		 *
		 * @param command
		 * @return new string command with stderr to stdout, useful with erebos::cmd()
		 */
		inline std::string stderr_to_stdout(const std::string &command) {
			return std::string(command).append(" 2>&1");
		}

#endif

		/*!
		 * @brief base64 class
		 */
		class base64 {
		public:
			/*!
			 * @brief encode a string using base64 cipher
			 * @param str : your string
			 * @param characters : (already set)
			 * @return new encoded string
			 */
			static inline std::string encode(const std::string &str,
					const char *characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/") {

				std::string string_encoded = "";

				const size_t str_len = str.length();
				size_t index = 0;

				while (index < str_len) {

					uint8_t ch1 = str[index];
					uint8_t ch2 = ((index + 1) < str_len) ? str[index + 1] : 0;
					uint8_t ch3 = ((index + 2) < str_len) ? str[index + 2] : 0;

					uint8_t ch1_temp = (ch1 >> 0x02);
					uint8_t ch2_temp = ((ch1 & 0x03) << 0x04) | (ch2 >> 0x04);
					uint8_t ch3_temp = ((ch2 & 0x0F) << 0x02) | (ch3 >> 0x06);
					uint8_t ch4_temp = (ch3 & 0x3F);

					string_encoded += characters[ch1_temp];
					string_encoded += characters[ch2_temp];
					string_encoded += characters[ch3_temp];
					string_encoded += characters[ch4_temp];

					index += 3;
				}

				size_t padding;
				if (str_len % 3 == 0)
					padding = 0;
				else if (str_len % 3 == 1)
					padding = 2;
				else
					padding = 1;

				string_encoded.erase(string_encoded.end() - padding, string_encoded.end());
				while (padding--)
					string_encoded += "=";

				return string_encoded;
			}

			/*!
			 * @brief decode a previously encoded base64 string
			 * @param str : base64-encoded string
			 * @param characters : (already set)
			 * @return new decoded string
			 */
			static inline std::string decode(const std::string &str,
					const char *characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/") {

				ssize ch1_code;
				ssize ch2_code;
				ssize ch3_code;

				std::string string_decoded = "";

				const size_t str_len = str.length();
				size_t index = 0;

				while (index < str_len) {

					ssize index1_temp = index_of(characters, str[index + 0]);
					ssize index2_temp = index_of(characters, str[index + 1]);
					ssize index3_temp = index_of(characters, str[index + 2]);
					ssize index4_temp = index_of(characters, str[index + 3]);

					// First char code
					ch1_code = index1_temp << 0x02 | index2_temp >> 0x04;
					string_decoded += static_cast<char>(ch1_code);

					if (index3_temp & 0x80 || index4_temp & 0x80)
						break; // char not found (ie. '=', or not valid char)

					// Second char code
					ch2_code = (index2_temp << 0x04) | (index3_temp >> 0x02);
					string_decoded += static_cast<char>(ch2_code);

					// Third char code
					ch3_code = (index3_temp & 0x03) << 0x06 | (index4_temp & 0x3F);
					string_decoded += static_cast<char>(ch3_code);

					index += 4;
				}

				return string_decoded;
			}
		};
	}
}

#endif
