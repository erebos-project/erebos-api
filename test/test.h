#ifndef TEST_H
#define TEST_H

inline void OUTPUT() { std::cout << '\n'; }

template<typename First, typename ... Many>
inline void OUTPUT(const First &arg, const Many &... rest) {
	std::cout << arg;
	OUTPUT(rest...);
}

template <typename R> struct func_extract_ret_struct {
	typedef R(*func_ptr)();
	typedef R Type;
};

template <typename R, typename ... Parameters>
inline func_extract_ret_struct<R> func_extract_ret(R(*func_ptr)(Parameters...)) {
    return func_extract_ret_struct<R>();
}

// This macro returns the return type of a function
#define FUNC_RETURN_TYPE(funcname) decltype(func_extract_ret(&funcname))::Type

//#define TEST_ABORT_IF_FAIL

// You should not use these macros
#define __FUNCTION_ERROR_OUTPUT(func_ptr) \
	OUTPUT("\t!!" func_ptr " returned an unexpected result\n")

#define __FUNCTION_VTYPES_EXPECTED(got,expect) \
	OUTPUT("\tDetails below:\n\t\tGot result: \'" got "\', expected: \'" expect "\'\n")

#define __FATAL_ABORT_TESTING() \
	OUTPUT("ExitInfo: Based on given rules for testing, this is going to terminate!!\n"); \
	exit(1)
// You should not use these macros --


// Shows message as below
#define TEST_MODULE(module_name) \
					OUTPUT("*** Starting testing for module: " module_name)

// Initialize testing
#define TEST_INIT() std::uint32_t final_res = 0;

// Use this macro to declare the start of testing a function
#define TEST_START(function)	\
				{	\
					OUTPUT("---> RunTest/Start: ", #function, " function is being tested...\n");	\
					auto curr_function_name = #function;	\
					unsigned int function_fails = 0;		\
					auto func_ptr = function;	\
					FUNC_RETURN_TYPE(function) res;


// Use this macro to declare the end of testing a function
#define TEST_END()	\
					OUTPUT("--> EndTest: test on function ", curr_function_name, " done, see result below\n"); \
					if(!function_fails) \
						OUTPUT("EndTest/Success: ", curr_function_name, " passed all tests\n"); \
					else \
						OUTPUT("EndTest/Error: ", curr_function_name, " did not pass some tests\n");	\
				}


#ifndef TEST_ABORT_IF_FAIL

#define TEST_CHECK(expected)	\
					if(expected != res) {	\
						__FUNCTION_ERROR_OUTPUT(curr_function_name);	\
						__FUNCTION_VTYPES_EXPECTED(res, expected); \
						final_res++;	\
						function_fails++;	\
					}
#else
#define TEST_CHECK(expected) \
					if(a != res) { \
						__FUNCTION_ERROR_OUTPUT(curr_function_name); \
						__FUNCTION_VTYPES_EXPECTED(res, expected); \
						__FATAL_ABORT_TESTING(); \
					}

#endif	// TEST_ABORT_IF_FAIL


// Use this macro to execute a function returning a value
#define TEST_EXEC(...) res = func_ptr(__VA_ARGS__)


// Use this macro to execute a function returning void
#define TEST_EXEC_VOID(...) func_ptr(__VA_ARGS__)


#endif
