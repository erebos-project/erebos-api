#include "test.h"
#include "native.h"

using namespace erebos;

int main(int argc, char const *argv[]) {

	// functions in the proc namespace must be manually tested

	NEW_MODULE_TEST("native");


	BEGIN_TEST PRE_CALL(proc::get_pid);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(proc::get_pid_by_name);
		// Empty test
	END_TEST();


#ifdef WINDOWS

	BEGIN_TEST PRE_CALL(proc::get_pid_by_win_name);
		// Empty test
	END_TEST();

#endif


	BEGIN_TEST PRE_CALL(proc::kill);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(proc::mem_read);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(proc::mem_write);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(proc::mem_lock);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(proc::mem_unlock);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(file::get_dir_file_list);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(file::get_dir_folder_list);
		// Empty test
	END_TEST();

	BEGIN_TEST PRE_CALL(file::get_folder_exists);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(file::get_size);
		// Empty test
	END_TEST();


#ifdef LINUX

	BEGIN_TEST PRE_CALL(file::readlink);
		// Empty test
	END_TEST();

#endif


	BEGIN_TEST PRE_CALL_OVERLOAD(pipe_open, int, const std::string&, int*);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL_OVERLOAD(pipe_open, int, const std::string&, std::string&, int*);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(set_cwd);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(is_privileged);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(string_from_errno);
		// Empty test
	END_TEST();


	BEGIN_TEST PRE_CALL(_get_exe_path_);
		// Empty test
	END_TEST();


	END_MODULE_TEST();

	return 0;
}
