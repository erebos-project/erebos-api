/*
* stringutils.h
* Character and string handling utilities.
*/

#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

#include "platform_defs.h"

#include <string>
#include <sstream>

namespace erebos {

	namespace strutil {

		using ssize = long long;

		/*
		* bool is_literal(char c)
		* Checks wether the given character is a letter.
		*/
		inline bool is_literal(const char& c) {
			return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
		}

		/*
		* bool is_numeral(char c)
		* Checks wether the given character is a number.
		*/
		inline bool is_numeral(const char& c) {
			return (c >= '0') && (c <= '9');
		}

		/*
		* bool is_quotes(char c)
		* Checks wether the given character is a quote (" or ')
		*/
		inline bool is_quotes(const char& c) {
			return c == '\'' || c == '\"';
		}

		/*
		* bool is_literal(std::string s)
		* Checks wether the whole string is made of letters.
		*/
		inline bool is_literal(const std::string& s) {
			for (size_t i = 0; i < s.size(); ++i) {
				if(!is_literal(s[i]))
					return false;
			}
			return true;
		}

		/*
		* bool is_numeral(std::string)
		* Checks wether the given string is made of numbers.
		*/
		inline bool is_numeral(const std::string& s) {
			for (size_t i = 0; i < s.size(); ++i) {
				if(!is_numeral(s[i]))
					return false;
			}
			return true;
		}

		/*
		* std::string string_cut(std::string s, size_t offset, size_t size)
		* Returns a part of the specified string, starting from [offset] and reading [size] characters.
		*/
		inline std::string cut(const std::string& s, const size_t& offset, size_t size = 0) {
			std::string res;
			if(!size)
				size = s.size() - offset;
			res.reserve(size);
			for (size_t i = offset; i < offset + size; ++i)
				res += s[i];
			return res;
		}

		/*
		* string string_replace(std::string target, std::string replaced, std::string replacement, size_t n = 0)
		* Replace 'n' occurrences of 'replaced' with 'replacement'.
		*/
		inline void replace(std::string& target, const std::string& replaced,
										  const std::string& replacement, const size_t& n = 0) {
			const size_t replaced_length = replaced.length();
			size_t position = 0;
			size_t iterations = 0;

			while ((position = target.find(replaced, position) + 1) != std::string::npos) {
				target.replace(position, replaced_length, replacement);
				iterations++;

				if (iterations == n)
					break;
			}

		  //return target;
		}

		/*
		* std::string string_replace(std::string target, std::string replaced, std::string replacement, size_t n = 0)
		* Replace 'n' occurrences of 'replaced' with 'replacement'.
		*/
		inline void replace(std::string& target, const char& replaced,
							const char& replacement, const size_t& n = 0) {
			size_t iterations = 0;
			for (size_t i = 0; i < target.size(); ++i) {
				if(target[i] == replaced) {
					target[i] = replacement;
					iterations++;
				}

				if(iterations == n && n > 0)
					break;
			}
		}

		/*
		* std::string string_mul(std::string s, size_t times)
		* Ruby style string multiplication.
		* Returns a string made of [times] times [s].
		*/
		inline std::string mul(const std::string& s, const size_t& times) {
			std::string res;
			for (size_t i = 0; i < times; ++i)
				res += s;
			return res;
		}

		/*
		* const std::vector<std::string> split(const std::string& str, const char& splchr)
		* Splits a string based on spaces.
		* Returns an std::vector of std::strings.
		*/
		inline void split(const std::string& str, const char& splchr, std::vector<std::string>& output) {

			std::stringstream ss(str);
			std::string item;

			while (getline(ss, item, splchr))
				output.emplace_back(item);
		}

		/*
		* size_t index_of(const char array[], char element)
		* Return the index of the element into the array or -1 if doesn't exist
		*/
		inline ssize index_of(const char array[], const char& element) {
			for(ssize i = 0; i < static_cast<ssize>(std::string(array).size()); i++)
				if(array[i] == element)
					return i;

			return -1;
		}

		inline std::string encode_base64(const std::string& str,
			const char* characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/") {

			std::string string_encoded = "";

			const size_t str_len = str.length();
			size_t index = 0;

			while(index < str_len) {

				uint8_t ch1 = str[index];
				uint8_t ch2 = ((index + 1) < str_len) ? str[index + 1] : 0;
				uint8_t ch3 = ((index + 2) < str_len) ? str[index + 2] : 0;

				uint8_t ch1_temp = (ch1 >> 0x02);
				uint8_t ch2_temp = ((ch1 & 0x03) << 0x04) | (ch2 >> 0x04);
				uint8_t ch3_temp = ((ch2 & 0x0F) << 0x02) | (ch3 >> 0x06);
				uint8_t ch4_temp = (ch3  & 0x3F);

				string_encoded += characters[ch1_temp];
				string_encoded += characters[ch2_temp];
				string_encoded += characters[ch3_temp];
				string_encoded += characters[ch4_temp];

				index += 3;
			}

			size_t padding;
			if(str_len % 3 == 0)
				padding = 0;
			else if(str_len % 3 == 1)
				padding = 2;
			else
				padding = 1;

			string_encoded.erase(string_encoded.end() - padding, string_encoded.end());
			while(padding--)
				string_encoded += "=";

			return string_encoded;
		}

		inline std::string decode_base64(const std::string& str,
			const char* characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/") {

			ssize ch1_code;
			ssize ch2_code;
			ssize ch3_code;

			std::string string_decoded = "";

			const size_t str_len = str.length();
			size_t index = 0;

			while(index < str_len) {

				ssize index1_temp = index_of(characters, str[index+0]);
				ssize index2_temp = index_of(characters, str[index+1]);
				ssize index3_temp = index_of(characters, str[index+2]);
				ssize index4_temp = index_of(characters, str[index+3]);

				// First char code
				ch1_code =  index1_temp << 0x02  |  index2_temp >> 0x04;
				string_decoded += static_cast<char>(ch1_code);

				if(index3_temp & 0x80 || index4_temp & 0x80)
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

#if defined(LINUX)
		inline std::string& stderr_to_stdout(const std::string& command) {
			return std::string(command).append("2>&1");
		}
#endif

		/*
		* std::string convert_base64_mime(std::string str)
		* std::string string_encode_base64_mime(std::string str)
		* Converts the given ASCII string to Base64 MIME.
		*/
		inline std::string encode_base64_mime(const std::string& str) {
			return encode_base64(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
		}

		/*
		* std::string string_decode_base64_mime(std::string str)
		* Converts the given Base64 MIME string to ASCII.
		*/
		inline std::string decode_base64_mime(const std::string& str) {
			return decode_base64(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
		}

		/*
		* std::string string_encode_base64_url(std::string str)
		* Converts the given ASCII string to Base64 URL.
		*/
		inline std::string encode_base64_url(const std::string& str) {
			return encode_base64(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
		}

		/*
		* std::string string_decode_base64_url(std::string str)
		* Converts the given Base64 URL string to ASCII.
		wtfit
		inline std::string decode_base64_url(const std::string& str) {
			return decode_base64_url("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
		}*/
	}
}

#endif
