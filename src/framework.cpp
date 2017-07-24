#include "framework.h"
#include "stringutils.h"

using namespace erebos;
using namespace strutil;

std::string erebos::get_exe_path() {
	return file::get_path(_get_exe_path_());
}

std::string erebos::to_unix_slash(const std::string &s) {
	std::string from = s;
	strutil::replace(from, '\\', '/');
	return from;
}

bool erebos::get_prompt_answer(const std::string &message,
									 const std::string &error_message,
									 const bool &exit_on_error) {
	print(message, " [Y/n]");
	char res;
	std::cin >> res;

	if (res == 'y' || res == 'Y')
		return true;
	else if (res == 'n' || res == 'N')
		return false;
	else {
		println(error_message);
		if (exit_on_error)
			exit(-10);
		return false;
	}
}


std::string erebos::parse_quotes(const std::string &s) {

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


void erebos::parse_arg(const std::string &input, std::vector<std::string> &output) {
	for (size_t i = 0; i < input.size(); ++i) {
		std::string curr;

		if (input[i] == '\n' && input[i] == '\0')
			break;

		if (is_quotes(input[i])) {
			i++;
			while (!is_quotes(input[i]) && input[i] != '\n' && input[i]) {
				curr += input[i];
				i++;
			}
		} else {
			while (!is_quotes(input[i]) && input[i] != ' ' && input[i] != '\n' && input[i]) {
				curr += input[i];
				i++;
			}
		}

		output.emplace_back(curr);
	}
}
