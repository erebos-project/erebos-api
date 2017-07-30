#ifndef TEST_H
#define TEST_H

inline void OUTPUT() { std::cout << '\n'; }

template<typename First, typename ... Many>
inline void OUTPUT(const First &arg, const Many &... rest) {
	std::cout << arg;
	OUTPUT(rest...);
}

//#define TEST_ABORT_IF_FAIL

//you should not use these macros
#define __FUNCTION_ERROR_OUTPUT(funcname) \
	OUTPUT("\t!!" funcname " returned an unexpected result\n")

#define __FUNCTION_VTYPES_EXPECTED(got,expect) \
	OUTPUT("\tDetails below:\n\t\tGot result: \'" got "\', expected: \'" expect "\'\n")

#define __FATAL_ABORT_TESTING() \
	OUTPUT("ExitInfo: Based on given rules for testing, this is going to terminate!!\n"); \
	exit(1)
//you should not use these macros

//Shows message as below
#define TEST_MODULE(module_name) \
					OUTPUT("*** Starting testing for module: " module_name)

//Initialize testing
#define TEST_INIT() \
					std::string str_res = ""; \
					std::int32_t int_res = 0; \
					std::uint32_t final_res = 0; \
					std::string curr_function_name = "";	\
					std::int32_t last_int_input = 0;	\
					std::string last_str_input = ""

// Use this macro to declare the start of testing a function
#define TEST_START(function_name)	\
				{	\
					OUTPUT("---> RunTest/Start: ", function_name, " function is being tested...\n");	\
					curr_function_name = function_name;	\
					unsigned int function_fails = 0


// Use this macro to declare the end of testing a function
#define TEST_END()	\
					OUTPUT("--> EndTest: test on function ", curr_function_name, " done, see result below\n"); \
					if(!function_fails) \
						OUTPUT("EndTest/Success: ", curr_function_name, " passed all tests\n"); \
					else \
						OUTPUT("EndTest/Error: ", curr_function_name, " did not pass some tests\n");	\
				}

//std::string
#ifndef TEST_ABORT_IF_FAIL
#define TEST_CHECK_STDSTRING(expected)	\
					if(expected != str_res) {	\
						__FUNCTION_ERROR_OUTPUT(curr_function_name);	\
						__FUNCTION_VTYPES_EXPECTED(str_res,expected); \
						final_res++;	\
						function_fails++;	\
					}
#else
#define TEST_CHECK_STDSTRING(expected) \
					if(a != str_res) { \
						__FUNCTION_ERROR_OUTPUT(curr_function_name); \
						__FUNCTION_VTYPES_EXPECTED(str_res,expected); \
						__FATAL_ABORT_TESTING(); \
					}
#endif

//int32
#ifndef TEST_ABORT_IF_FAIL
#define TEST_CHECK_INT32(expected)	\
					if(expected != int_res) {	\
						__FUNCTION_ERROR_OUTPUT(curr_function_name);	\
						__FUNCTION_VTYPES_EXPECTED(str_res,expected); \
						final_res++;	\
						function_fails++;	\
					}
#else
#define TEST_CHECK_INT32(expected) \
					if(a != int_res) { \
						__FUNCTION_ERROR_OUTPUT(curr_function_name); \
						__FUNCTION_VTYPES_EXPECTED(str_res,expected); \
						__FATAL_ABORT_TESTING(); \
					}
#endif

/*
// Use this macro to check a function string return value
#ifndef TEST_ABORT_IF_FAIL
#define TEST_CHECK_EQUAL_STR(a)	\
					if(a != str_res) {	\
						__FUNCTION_ERROR_OUTPUT(curr_function_name);	\
						__FUNCTION_VTYPES_EXPECTED(str_res,a); \
						final_res++;	\
						function_fails++;	\
					}
#else
#define TEST_CHECK_EQUAL_STR(a) \
					if(a != str_res) { \
						__FUNCTION_ERROR_OUTPUT(curr_function_name); \
						__FUNCTION_VTYPES_EXPECTED(str_res,a); \
						__FATAL_ABORT_TESTING(); \
					}
#endif


// Use this macro to check a function integer (any integer or float type) return value
#define TEST_CHECK_EQUAL_INT(a)	\
					if(a != int_res) {	\
						__FUNCTION_ERROR_OUTPUT(curr_function_name);	\
						__FUNCTION_VTYPES_EXPECTED(a,int_res);	\
						final_res++;	\
						function_fails++;	\
					}


// Use this macro to check a function return value
#define TEST_CHECK_EQUAL(a, b)	\
					if(a != b) {	\
						__FUNCTION_ERROR_OUTPUT(curr_function_name);	\
						final_res++;	\
						function_fails++;	\
					}


 ============================
#define TEST_ERROR() __FUNCTION_ERROR_OUTPUT(curr_function_name);	\
									final_res++;	\
									function_fails++


// Use this macro to execute a function returning a string
#define TEST_EXEC_STR(...) str_res = FUNCNAME(__VA_ARGS__)


// Use this macro to execute a function returning an integer
#define TEST_EXEC_INT(...) int_res = FUNCNAME(__VA_ARGS__)


// Use this macro to execute a function returning void
#define TEST_EXEC(...) FUNCNAME(__VA_ARGS__)


// Use this macro to execute a function returning another type
#define TEST_EXEC_OTHER(output_variable, ...) output_variable = FUNCNAME(__VA_ARGS__)
*/


#endif
