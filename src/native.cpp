#include "native.h"

#if defined(WINDOWS)
#define WINDOWS_LEAN_AND_MEAN 1

#include <windows.h>
#include <wincrypt.h>
#include <tlhelp32.h>
#include "stringutils.h"

#if defined(_COMPILER_MSVC)
#define POPEN_F _popen
#define PCLOSE_F _pclose
#elif defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
#include <cstdio>
#define POPEN_F popen
#define PCLOSE_F pclose
#endif

// __stdcall ignored here
using CheckTokenMembership_ptr = BOOL(*)(HANDLE TokenHandle, PSID SidToCheck, PBOOL IsMember);

#elif defined(LINUX)
#define POPEN_F popen
#define PCLOSE_F pclose

#include "stringutils.h"
#include "file.h"

#include <unistd.h>
#include <sys/uio.h>
#include <linux/random.h>
#include <linux/limits.h>
#include <signal.h>
#include <dirent.h>
#include <syscall.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ftw.h>
#endif

std::string erebos::get_exe_path_()  {

#if defined(WINDOWS)
	char buff[256];
	int res = GetModuleFileName(NULL, buff, 256);

	if(!res)
		return "";

	return buff;

#elif defined(LINUX)

	std::stringstream ss;
	ss << "/proc/" << getpid() << "/exe";

	std::string exe_link = file::readlink(ss.str());

	return exe_link;
#endif
}


int erebos::proc::get_pid() {
#if defined(WINDOWS)
	return GetCurrentProcessId();
#elif defined(LINUX)
	return getpid();
#endif
}


int erebos::proc::get_pid_by_name(const std::string& name, std::vector<int>& output) {

#if defined(WINDOWS)
	PROCESSENTRY32 processEntry;
	HANDLE handle;

	if (!(handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)))
		return -1;

	// We must initialize this word, otherwise Process32First fails.
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	int retval = 0;

	if (Process32First(handle, &processEntry)) {
		do {
			if (!lstrcmp(processEntry.szExeFile, name.c_str()))
				output.push_back(processEntry.th32ProcessID);
		} while (Process32Next(handle, &processEntry));

		if (GetLastError() != 0)
			retval = -3;
	}
	else if (GetLastError() != 0)
		retval = -2;

	if (!CloseHandle(handle))
		retval = -4;

	return retval;
#elif defined(LINUX)
    std::vector<std::string> running_procs;
    if(!file::get_dir_folder_list("/proc",running_procs))
		return -1;

	char comm_path[PATH_MAX];
	for(const auto& proc_dir : running_procs) {
		if(strutil::is_numeral(proc_dir)) {
			snprintf(comm_path,PATH_MAX,"/proc/%s/comm",proc_dir.c_str());
			std::string content = file::read(comm_path);
			strutil::chomp(content);
			if(content == name)
				output.push_back(std::stoi(proc_dir));
		}
	}

	return 0;
#endif
}

#if defined(WINDOWS)
int erebos::proc::get_pid_by_win_name(const std::string& win_name) {

	HWND win_handle = FindWindow(nullptr, static_cast<LPCSTR>(win_name.c_str()));
	if(!win_handle)
		return -1;

	DWORD process_id;
	GetWindowThreadProcessId(win_handle, &process_id);

	return process_id;
}
#endif


bool erebos::proc::kill(const int& pid) {
#if defined(WINDOWS)
	HANDLE proc_handle = OpenProcess(PROCESS_TERMINATE, false, pid);
	return !TerminateProcess(proc_handle, 0);
#elif defined(LINUX)
	return !::kill(pid, SIGTERM);
#endif
}

int erebos::proc::mem_read(const int& pid, const size_t& address, char* result, const size_t& size ) {

#if defined(WINDOWS)
	HANDLE process_handle;

	process_handle = OpenProcess(PROCESS_VM_READ, FALSE, pid);
	if(!process_handle)
		return '\0';

	size_t bytecount;
	if (!ReadProcessMemory(process_handle, (LPVOID)address,
			result, size, (SIZE_T*) &bytecount))
		return 0;

	if (!CloseHandle(process_handle))
		return 0;

	return (int) bytecount;

#elif defined(LINUX)
	iovec local;
	iovec remote;

	local.iov_base = result;
	local.iov_len = size;

	remote.iov_base = (void *) address;
	remote.iov_len = size;

	ssize_t bytes = process_vm_readv(pid, &local, 1, &remote, 1, 0);
	if (bytes < 0)
		return 0;

	return (int) bytes;
#endif
}

int erebos::proc::mem_write(const int& pid, const size_t& address, char* data, const size_t& size) {

#if defined(WINDOWS)

	HANDLE process_handle;
	SIZE_T bytecount = 0;
	LPCVOID value_ptr = static_cast<LPCVOID>(&data);

	process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if(!process_handle)
		return 0;

	if (!WriteProcessMemory(process_handle, (LPVOID)address,
			value_ptr, static_cast<SIZE_T>(size), &bytecount))
		return 0;

	if (!CloseHandle(process_handle))
		return 0;

	return (int) bytecount;

#elif defined(LINUX)

	iovec local;
	iovec remote;

	local.iov_base = data;
	local.iov_len = size;

	remote.iov_base = (void*) address;
	remote.iov_len = size;

	ssize_t bytes = process_vm_writev(pid, &local, 1, &remote, 1, 0);
	if (bytes < 0)
		return 0;

	return (int) bytes;

#endif
}


bool erebos::proc::mem_lock(void* address, const size_t& size) {

#if defined(WINDOWS)
	return VirtualLock(address, size);

#elif defined(LINUX)
	return !mlock(address, size);
#endif
}

bool erebos::proc::mem_unlock(void* address, const size_t& size) {

#if defined(WINDOWS)
	return VirtualUnlock(address, size);

#elif defined(LINUX)
	return !munlock(address, size);
#endif
}

bool erebos::is_privileged() {

#if defined(WINDOWS)

	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	BOOL b = AllocateAndInitializeSid(&NtAuthority,
									 2,
									 SECURITY_BUILTIN_DOMAIN_RID,
									 DOMAIN_ALIAS_RID_ADMINS,
									 0, 0, 0, 0, 0, 0,
									 &AdministratorsGroup);

	HINSTANCE lib = LoadLibrary("Advapi32.dll");

	if(!lib)
		return false;

	CheckTokenMembership_ptr checkTokenMembership = (CheckTokenMembership_ptr) GetProcAddress(lib, "CheckTokenMembership");

	FreeLibrary(lib);

	if(!lib)
		return false;

	if(b) {
		if (!checkTokenMembership(0, AdministratorsGroup, &b))
			b = FALSE;

		FreeSid(AdministratorsGroup);
	}

	return b != 0;

#elif defined(LINUX)

	return geteuid() == 0;

#endif
}

int erebos::get_random_secure() {

#if defined(WINDOWS)

	HCRYPTPROV hProv;

	int res;

	if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
		BYTE dbData[4];
		if(CryptGenRandom(hProv, 4, dbData))
			res = (dbData[0] << 24) | (dbData[1] << 16) | (dbData[2] << 8) | dbData[3];
		else
			return 0;
	} else
		return 0;

	CryptReleaseContext(hProv, 0);

	return res;

#elif defined(LINUX) && defined(SYS_getrandom) && defined(GRND_RANDOM)

	int res;
	syscall(SYS_getrandom, &res, 4, GRND_RANDOM);

	return res;
#endif
}


bool erebos::file::get_dir_file_list(const std::string& dir, std::vector<std::string>& output) {

#if defined(WINDOWS)
	HANDLE           hFile;
	WIN32_FIND_DATA  wfd;
	TCHAR            path_ch[_MAX_PATH];

	// Compatible with Unix and Windows string format
	std::string path = dir;
	if (path.find("/") != std::string::npos)
		erebos::strutil::replace(path, '/', '\\');

	path.append("\\*");

	path_ch[path.size()] = '\0';
	std::copy(path.begin(), path.end(), path_ch);

	hFile = FindFirstFile(path_ch, &wfd);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	bool retval = true;

	do {
		if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_NORMAL))
			output.emplace_back(wfd.cFileName);
	} while(FindNextFile(hFile, &wfd) != 0);

	if (GetLastError() != 0)
		retval = false;

	if (!CloseHandle(hFile) && retval)
		retval = false;

	return retval;
#elif defined(LINUX)

	DIR* handle = opendir(dir.c_str());
	if(!handle)
		return false;

	dirent *dir_entry;
	while((dir_entry = readdir(handle)))
		if(dir_entry->d_type == DT_REG)
			output.emplace_back(dir_entry->d_name);

	if (closedir(handle))
		return false;
#endif

	return true;
}


bool erebos::file::get_dir_folder_list(const std::string& dir, std::vector<std::string>& output) {

#if defined(WINDOWS)
	HANDLE           hFile;
	WIN32_FIND_DATA  wfd;
	TCHAR            path_ch[_MAX_PATH];

	// Compatible with Unix and Windows string format
	std::string path = dir;

	if (path.find("/") != std::string::npos)
		erebos::strutil::replace(path, '/', '\\');

	path.append("\\*");

	path_ch[path.size()] = '\0';
	std::copy(path.begin(), path.end(), static_cast<char*>(path_ch));

	hFile = FindFirstFile(path_ch, &wfd);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	bool retval = true;

	do {
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			output.emplace_back(wfd.cFileName);
	} while(FindNextFile(hFile, &wfd) != 0);

	if (GetLastError() != 0)
		retval = false;

	if (!CloseHandle(hFile) && retval)
		retval = false;

	return retval;

#elif defined(LINUX)

	DIR* handle = opendir(dir.c_str());
	if(!handle)
		return false;

	dirent *dir_entry;
	while((dir_entry = readdir(handle)))
		if(dir_entry->d_type == DT_DIR)
			output.emplace_back(dir_entry->d_name);

	if(closedir(handle))
		return false;
#endif
	return true;
}


bool erebos::file::get_folder_exists(const std::string& foldername) {

#if defined(WINDOWS)
	DWORD dwAttributes = GetFileAttributes(foldername.c_str());

	return dwAttributes != INVALID_FILE_ATTRIBUTES &&
			(dwAttributes &  FILE_ATTRIBUTE_DIRECTORY);

#elif defined(LINUX)
	return !access(foldername.c_str(), F_OK);
#endif
}


int erebos::file::get_size(const std::string& filename) {

#if defined(WINDOWS)
	HANDLE fd = CreateFile(filename.c_str(), GENERIC_READ, 0, nullptr,
							OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (!fd)
		return -1;

	DWORD size;
	GetFileSize(fd, &size);

	if (!CloseHandle(fd))
		return -2;

	return size;

#elif defined(LINUX)
	struct stat st;
	if (stat(filename.c_str(), &st) == -1)
		return -1;

	return static_cast<int>(st.st_size);
#endif
}


bool erebos::file::remove(const std::string& filename) {

#if defined(WINDOWS)
	return DeleteFile(filename.c_str()) != 0;
#elif defined(LINUX)
	return unlink(filename.c_str()) == 0;
#endif

}


#ifdef LINUX
int remove_callback(const char *filepath, const struct stat *st, int flag, struct FTW *buffer) {

	return ::remove(filepath);
}
#endif



bool erebos::file::remove_dir(const std::string& dirname) {

#if defined(WINDOWS)

	char buffer[_MAX_DIR];
	snprintf(buffer, _MAX_DIR, "%s\0\0", dirname.c_str());


	// This function needs paths to be double null terminated

	SHFILEOPSTRUCT opstruct = {
		nullptr,
		FO_DELETE,
		buffer,
		nullptr,
		FOF_NOCONFIRMATION |
		FOF_NOERRORUI |
		FOF_SILENT,
		false,
		0,
		nullptr
	};

    return SHFileOperation(&opstruct) == 0;

#elif defined(LINUX)

	return nftw(dirname.c_str(), remove_callback, 64, FTW_DEPTH | FTW_PHYS) == 0;

#endif

}


int erebos::cmd(const std::string& command, int* retval) {

	FILE* open_pipe = POPEN_F(command.c_str(),"r");
	if (!open_pipe)
		return -1;

	errno = 0;
	int res = PCLOSE_F(open_pipe);
	if(retval)
		*retval = res;

	if (res == -1 && errno != 0)
		return -2;

	return 0;
}


int erebos::cmd(const std::string& command, std::string& output, int* retval) {

	FILE* open_pipe = POPEN_F(command.c_str(),"r");
	if (!open_pipe)
		return -1;

	std::stringstream outstream;

	char each_line[BUFSIZ];
	while (fgets(each_line, BUFSIZ, open_pipe))
		outstream << each_line;

	output = outstream.str();

	errno = 0;
	int res = PCLOSE_F(open_pipe);

	if(retval)
		*retval = res;

	if (res == -1 && errno != 0)
		return -2;

	return 0;
}


#if defined(LINUX)
std::string erebos::file::readlink(const std::string& filename) {

	struct stat link_stat;

	ssize_t res = lstat(filename.c_str(), &link_stat);
	if (res == -1)
		return "";

	char buff[PATH_MAX];
	res = ::readlink(filename.c_str(), buff, PATH_MAX);
	if (res == -1)
		return "";

	buff[res] = '\0';
	return buff;
}
#endif


std::string erebos::string_from_errno(const int& errn) {

#if defined(LINUX)
	return strerror(errn);

#elif defined(WINDOWS)

	LPSTR target;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errn, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR) &target, 0, NULL);

	std::string target_stds = static_cast<char*>(target);
	target_stds.erase(target_stds.end() - 2, target_stds.end()); // erase:\r\n

	LocalFree(target);

	return target_stds;
#endif
}
