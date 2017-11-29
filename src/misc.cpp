#include "misc.h"
#include "stringutils.h"

using namespace erebos;
using namespace strutil;

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
