#ifndef TEST_H
#define TEST_H

inline void OUTPUT() { std::cout << '\n'; }
template<typename First, typename ... Many>
inline void OUTPUT(const First &arg, const Many &... rest) {
	std::cout << arg;
	OUTPUT(rest...);
}


// Use this macro to declare the start of testing a function
#define TEST_START(function_name)	{	OUTPUT("Testing ", function_name, " function...");	\
										curr_function_name = function_name;	\
										unsigned int function_fails = 0


// Use this macro to declare the end of testing a function
#define TEST_END()	if(function_fails == 0) OUTPUT("SUCCESS: ", curr_function_name, " passed all tests\n"); \
					else OUTPUT("ERROR: ", curr_function_name, " did not pass some tests\n");	\
					}


// Use this macro to check a function string return value
#define TEST_CHECK_EQUAL_STR(a)	if(a != str_res) {	\
									OUTPUT("ERROR: ", curr_function_name, " returned an unexpected result:");	\
									OUTPUT("\t\'", str_res, "\' instead of \'", a, "\'\n");	\
									final_res++;	\
									function_fails++;	\
								}


// Use this macro to check a function integer (any integer or float type) return value
#define TEST_CHECK_EQUAL_INT(a)	if(a != int_res) {	\
									OUTPUT("ERROR: ", curr_function_name, " returned an unexpected result:");	\
									OUTPUT("\t\'", var_to_string(int_res), "\' instead of \'", var_to_string(a), "\'\n");	\
									final_res++;	\
									function_fails++;	\
								}


// Use this macro to check a function return value
#define TEST_CHECK_EQUAL(a, b)	if(a != b) {	\
									OUTPUT("ERROR: ", curr_function_name, " returned an unexpected result\n");	\
									final_res++;	\
									function_fails++;	\
								}


// Use this macro to execute a function returning a string
#define TEST_EXEC_STR(...) str_res = FUNCNAME(__VA_ARGS__)


// Use this macro to execute a function returning an integer
#define TEST_EXEC_INT(...) int_res = FUNCNAME(__VA_ARGS__)


// Use this macro to execute a function returning void
#define TEST_EXEC(...) FUNCNAME(__VA_ARGS__)


// Use this macro to execute a function returning another type
#define TEST_EXEC_OTHER(output_variable, ...) output_variable = FUNCNAME(__VA_ARGS__)


#define TEST_CONFIG() 	std::string str_res = ""; \
						int int_res = 0; \
						unsigned int final_res = 0; \
						std::string curr_function_name = "";	\
						int last_int_input = 0;	\
						std::string last_str_input = ""


#endif
