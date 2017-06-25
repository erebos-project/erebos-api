/*
* stringutils.h
* Character and string handling utilities.
*/

#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

#include <string>
#include <sstream>

namespace erebos {

	namespace strutil {

		/*
		* bool is_literal(char c)
		* Checks wether the given character is a letter.
		*/
		inline bool is_literal(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

		/*
		* bool is_numeral(char c)
		* Checks wether the given character is a number.
		*/
		inline bool is_numeral(char c) { return (c >= '0') && (c <= '9'); }

		/*
		* bool is_quotes(char c)
		* Checks wether the given character is a quote (" or ')
		*/
		inline bool is_quotes(char c) { return c == '\'' || c == '\"'; }

		/*
		* bool is_literal(std::string s)
		* Checks wether the whole string is made of letters.
		*/
		inline bool is_literal(std::string s) {
			const size_t size = s.size();
			for (int i = 0; i < size; ++i) {
				if(!is_literal(s[i])) return false;
			}
			return true;
		}

		/*
		* bool is_numeral(std::string)
		* Checks wether the given string is made of numbers.
		*/
		inline bool is_numeral(std::string s) {
			const size_t size = s.size();
			for (int i = 0; i < size; ++i) {
				if(!is_numeral(s[i])) return false;
			}
			return true;
		}

		/*
		* std::string string_cut(std::string s, size_t offset, size_t size)
		* Returns a part of the specified string, starting from [offset] and reading [size] characters.
		*/
		inline std::string cut(std::string s, size_t offset, size_t size = 0) {
			std::string res;
			if(!size) size = s.size() - offset;
			res.reserve(size);
			for (int i = offset; i < offset + size; ++i)
				res += s[i];
			return res;
		}

		/*
		* string string_replace(std::string target, std::string replaced, std::string replacement, size_t n = 0)
		* Replace 'n' occurrences of 'replaced' with 'replacement'.
		*/
		inline std::string replace(std::string target, std::string replaced,
										  std::string replacement, size_t n = 0) {
			size_t position = -1;
			int replaced_length  = replaced.length();
			int iterations = 0;

			while ((position = target.find(replaced, position + 1)) != std::string::npos) {
				target.replace(position, replaced_length, replacement);
				iterations++;

				if (iterations == n)
					break;
			}

		  return target;
		}

		/*
		* std::string string_replace(std::string target, std::string replaced, std::string replacement, size_t n = 0)
		* Replace 'n' occurrences of 'replaced' with 'replacement'.
		*/
		inline std::string replace(std::string target, char replaced, char replacement, size_t n = 0) {

			int iterations = 0;
			for (int i = 0; i < target.size(); ++i) {
				if(target[i] == replaced) {
					target[i] = replacement;
					iterations++;
				}

				if(iterations == n && n > 0)
					break;
			}
			return target;
		}

		/*
		* std::string string_mul(std::string s, size_t times)
		* Ruby style string multiplication.
		* Returns a string made of [times] times [s].
		*/
		inline std::string mul(std::string s, size_t times) {
			std::string res;
			for (int i = 0; i < times; ++i)
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
				output.push_back(item);
		}

		/*
		* size_t string_index_of(const char array[], char element)
		* Return the index of the element into the array or -1 if doesn't exist
		*/
		inline size_t index_of(const char array[], char element) {

			for(size_t i = 0; i < (std::string(array).size()); i++)
				if(array[i] == element) return i;

			return -1;
		}

		inline std::string encode_base64(std::string str,
			const char* characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/") {

			std::string string_encoded = "";
			size_t str_len = str.length();

			int index = 0;

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
			while(padding--) string_encoded += "=";

			return string_encoded;
		}

		inline std::string decode_base64(std::string str,
			const char* characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/") {

			uint8_t ch1_code, ch2_code, ch3_code;
			std::string string_decoded = "";

			size_t str_len = str.length();
			int index = 0;

			while(index < str_len) {

				uint8_t index1_temp = index_of(characters, str[index+0]);
				uint8_t index2_temp = index_of(characters, str[index+1]);
				uint8_t index3_temp = index_of(characters, str[index+2]);
				uint8_t index4_temp = index_of(characters, str[index+3]);

				// First char code
				ch1_code =  index1_temp << 0x02  |  index2_temp >> 0x04;
				string_decoded += ch1_code;

				if(index3_temp & 0x80) break; // char not found (ie. '=', or not valid char)

				// Second char code
				ch2_code = (index2_temp << 0x04) | (index3_temp >> 0x02);
				string_decoded += ch2_code;

				if(index4_temp & 0x80) break;

				// Third char code
				ch3_code = (index3_temp & 0x03) << 0x06 | (index4_temp & 0x3F);
				string_decoded += ch3_code;

				index += 4;
			}

			return string_decoded;
		}

		/*
		* std::string convert_base64_mime(std::string str)
		* std::string string_encode_base64_mime(std::string str)
		* Converts the given ASCII string to Base64 MIME.
		*/
		inline std::string encode_base64_mime(std::string str) {

			return encode_base64(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
		}

		/*
		* std::string string_decode_base64_mime(std::string str)
		* Converts the given Base64 MIME string to ASCII.
		*/
		inline std::string decode_base64_mime(std::string str) {

			return decode_base64(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
		}

		/*
		* std::string string_encode_base64_url(std::string str)
		* Converts the given ASCII string to Base64 URL.
		*/
		inline std::string encode_base64_url(std::string str) {

			return encode_base64(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
		}

		/*
		* std::string string_decode_base64_url(std::string str)
		* Converts the given Base64 URL string to ASCII.
		*/
		inline std::string decode_base64_url(std::string str) {

			return decode_base64_url("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
		}
	}
}

#endif
