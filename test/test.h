#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <sstream>

inline void OUTPUT() { std::cout << '\n'; }

template<typename First, typename ... Many>
inline void OUTPUT(const First &arg, const Many &... rest) {
	std::stringstream dst;
	dst << arg;

	std::cout << dst.str(); 
	OUTPUT(rest...);
}


template <typename ReturnType> 
struct func_extract_ret_struct {
	//typedef R(*func_ptr)();
	typedef ReturnType Type;
};

template <typename ReturnType, typename ... Parameters>
inline func_extract_ret_struct<ReturnType> func_extract_ret(ReturnType(*func_ptr)(Parameters...)) {
	return func_extract_ret_struct<ReturnType>();
}

// You should not use these macros --
#define __FUNC_RETURN_TYPE(funcname) \
	decltype(func_extract_ret(&funcname))::Type

#define __FUNCTION_ERROR_OUTPUT() \
	OUTPUT("\tRunTest/Fail: unexpected result :'( ")

#define __FUNCTION_VTYPES_EXPECTED(got,expect) \
	OUTPUT("\t!! Details below:\n\t\tGot result: \'", got, "\', expected: \'", expect, "\'")

#define __FUNCTION_CALLBACK_OUTPUT() \
	OUTPUT("\tRunTest/Callback: calling back function...")

#define __FUNCTION_PASS_OUTPUT() \
	OUTPUT("\tRunTest/Pass: result match :D")

#define __FATAL_ABORT_TESTING() \
	OUTPUT("ExitInfo: Based on given rules for testing, this is going to terminate!!"); \
	exit(1)
// You should not use these macros --


// Shows message as below
#define BEGIN_TEST_MODULE() \
					OUTPUT("Test/ModuleBegin: *** Starting testing for module: ", module_name)

#define END_TEST_MODULE() \
					OUTPUT("Test/ModuleEnd:   *** End testing for module: ", module_name)

// Initialize testing
#define TEST_INIT(modname) \
	constexpr char module_name[] = modname; \
	std::uint32_t final_res = 0

// Use this macro to declare the start of testing a function
//new scope begins here
#define TEST_START(function)	\
				{	\
					constexpr char lscope_test_funcname[] = #function; \
					OUTPUT("\n---> RunTest/Start: ", lscope_test_funcname, " function is being tested...");	\
					unsigned int function_fails = 0;		\
					auto func_ptr = function;	\
					__FUNC_RETURN_TYPE(function) res;


// Use this macro to declare the end of testing a function
#define TEST_END()	\
					OUTPUT("\tEndTest: test on function ", lscope_test_funcname, " done, see result below"); \
					if(!function_fails) \
						OUTPUT("--> EndTest/Success: ", lscope_test_funcname, " passed all tests\n"); \
					else \
						OUTPUT("--> EndTest/Error: ", lscope_test_funcname, " did not pass some tests\n");	\
				} //out of scope


#ifndef TEST_ABORT_IF_FAIL
#define TEST_CHECK(expected)	\
					if(expected != res) {	\
						__FUNCTION_ERROR_OUTPUT();	\
						__FUNCTION_VTYPES_EXPECTED(res, expected); \
						final_res++;	\
						function_fails++;	\
					} else \
						__FUNCTION_PASS_OUTPUT()
#else
#define TEST_CHECK(expected) \
					if(expected != res) { \
						__FUNCTION_ERROR_OUTPUT(); \
						__FUNCTION_VTYPES_EXPECTED(res, expected); \
						__FATAL_ABORT_TESTING(); \
					} else \
						__FUNCTION_PASS_OUTPUT();
#endif	// TEST_ABORT_IF_FAIL


// Use this macro to execute a function returning a value
#define TEST_EXEC(...) \
	__FUNCTION_CALLBACK_OUTPUT(); \
	res = func_ptr(__VA_ARGS__)


// Use this macro to execute a function returning void
#define TEST_EXEC_VOID(...) \
	__FUNCTION_CALLBACK_OUTPUT(); \
	func_ptr(__VA_ARGS__)


#endif
