/*
Unit testing macros,
should be used with erebos framework only!
*/
#ifndef TEST_H
#define TEST_H

#include <iostream>

//Very thanks to Matth :) :) :)
template<typename _ReturnType>
struct Function {
	typedef _ReturnType Type;
};

template<typename TyRet, typename ... ManyParameters>
inline Function<TyRet> extract_retype(TyRet(*target_fptr)(ManyParameters...)) {
	return Function<TyRet>();
}

#define __DECLSYM_FUNCNAME(name) \
	constexpr char function_name[] = name

#define NEW_MODULE_TEST(modulename) \
	constexpr char module_name[] = modulename; \
	int failure = 0; \
	std::cout << "*** Test/ModuleTests/Start: starting tests for module: " << module_name << '\n'

#define END_MODULE_TEST() \
	std::cout << '\n'; \
	if(failure) \
		std::cerr << "!!! Test/FinalResult: one or more tests failed, see above.\n"; \
	else \
		std::cout << "+++ Test/FinalResult: all tests passed successfully\n"; \
	std::cout << "*** Test/ModuleTests/End: tests finished for module: " << module_name << std::endl; \
	return failure

#define BEGIN(func_callback) \
	{ \
		__DECLSYM_FUNCNAME(#func_callback); \
		std::cout << "\n\t--> RunTest/Function/Begin: running test for function: " << function_name; \
		decltype(extract_retype(&func_callback))::Type retv; \
		auto cb = func_callback

#define BEGIN_OVERLOAD(func_callback, ret_type, ...) \
	{ \
		__DECLSYM_FUNCNAME(#func_callback); \
		std::cout << "\n\t--> RunTest/Function/Begin: running test for function: " \
			<< #ret_type << ' ' << function_name << '(' << #__VA_ARGS__ << ")\n"; \
		ret_type retv; \
		ret_type (*cb)(__VA_ARGS__) = func_callback

#define BEGIN_VOID(func_callback, ...) \
	{ \
		__DECLSYM_FUNCNAME(#func_callback); \
		std::cout << "\n\t--> RunTest/Function/Begin: running test for function: void " \
			<< function_name << '(' << #__VA_ARGS__ << ")\n"; \
		void (*cb)(__VA_ARGS__) = func_callback

#define WITHOUT_RETV
#define WITH_RETV retv = 

#define CALLBACK(...) \
		cb(__VA_ARGS__)

#define END() \
		std::cout << "\n\t--> RunTest/Function/End: test for function " << function_name << " done.\n"; \
	}

#endif //TEST_H