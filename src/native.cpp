#include "native.h"
#include "framework.h"

#if defined(WINDOWS)
#define WINDOWS_LEAN_AND_MEAN 1
#include <windows.h>
#include <wincrypt.h>
#include <tlhelp32.h>
#elif defined(LINUX)
#include <unistd.h>
#include <sys/uio.h>
#include <linux/random.h>
#include <signal.h>
#include <dirent.h>
#include <syscall.h>
#include <sys/stat.h>
#include <sys/mman.h>
#endif

std::string erebos::get_exe_path_()  {
#ifdef WINDOWS
	char buff[256];
	int res = GetModuleFileName(NULL, buff, 256);
	if(!res)
		return "";

	return buff;
#elif defined(LINUX)
	char buff[512];
	std::stringstream ss;
	ss << "/proc/" << getpid() << "/exe";

	ssize_t size = readlink(ss.str().c_str(), buff, 512);
	if(size > 512 || !size)
		return "";

	buff[size] = '\0';

	return buff;
#endif
}


int erebos::proc::get_pid() {
#ifdef WINDOWS
	return GetCurrentProcessId();
#elif defined(LINUX)
	return getpid();
#endif
}


int erebos::proc::get_pid_by_name(const std::string& name) {
	int pid = -1;
#ifdef WINDOWS
	PROCESSENTRY32 processEntry;
	HANDLE handle;

	handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// We must initialize this word, otherwise Process32First fails.
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	if(Process32First(handle, &processEntry)) {
		do {
			if (!lstrcmp(processEntry.szExeFile, name.c_str())) {
				pid = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(handle, &processEntry));
	}

	CloseHandle(handle);
#elif defined(LINUX)

#endif
	return pid;
}

#ifdef WINDOWS
int erebos::proc::get_pid_by_win_name_w(const std::string& win_name) {
	HWND win_handle = FindWindow(nullptr, static_cast<LPCSTR>(win_name.c_str()));

	if(!win_handle)
		return -1;

	DWORD process_id;
	GetWindowThreadProcessId(win_handle, &process_id);

	return process_id;
}
#endif


bool erebos::proc::kill(const int& pid) {
#ifdef WINDOWS
	HANDLE proc_handle = OpenProcess(PROCESS_TERMINATE, false, pid);
	return !TerminateProcess(proc_handle, 0);
#elif defined(LINUX)
	return !::kill(pid, SIGKILL);
#endif
}

#ifdef WINDOWS
size_t erebos::proc::mem_read(const std::uint32_t pid, const size_t& address, char* result, const size_t& size ) {
	HANDLE process_handle;

	process_handle = OpenProcess(PROCESS_VM_READ, FALSE, pid);
	if(!process_handle)
		return '\0';

	size_t bytecount = ReadProcessMemory(process_handle, (LPVOID) address,
								 result, size, (SIZE_T*) &bytecount);

	CloseHandle(process_handle);

	return bytecount;
#elif defined(LINUX)
ssize_t erebos::proc::mem_read(const std::uint32_t pid, const size_t& address, char* result, const size_t& size ) {
	iovec local;
	iovec remote;

	local.iov_base = result;
	local.iov_len = size;

	remote.iov_base = (void *) address;
	remote.iov_len = size;

	return process_vm_readv(pid, &local, 1, &remote, 1, 0);
#endif
}

#ifdef WINDOWS
size_t mem_write(const std::uint32_t& pid, const size_t& address, char* data, const size_t& size) {
	HANDLE process_handle;
	SIZE_T bytecount = 0;
	LPCVOID value_ptr = static_cast<LPCVOID>(&data);

	process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if(!process_handle)
		return 0;

	WriteProcessMemory(process_handle, (LPVOID) address,
					   value_ptr, static_cast<SIZE_T>(size), &bytecount);

	CloseHandle(process_handle);

	return bytecount;
#elif defined(LINUX)
ssize_t mem_write(const std::uint32_t& pid, const size_t& address, char* data, const size_t& size) {
	iovec local;
	iovec remote;

	local.iov_base = data;
	local.iov_len = size;

	remote.iov_base = (void*) address;
	remote.iov_len = size;

	return process_vm_writev(pid, &local, 1, &remote, 1, 0);
#endif
}


bool erebos::proc::mem_lock(void* address, const size_t& size) {
#ifdef WINDOWS
	return VirtualLock(address, size);
#elif defined(LINUX)
	return !mlock(address, size);
#endif
}

bool erebos::proc::mem_unlock(void* address, const size_t& size) {
#ifdef WINDOWS
	return VirtualUnlock(address, size);
#elif defined(LINUX)
	return !munlock(address, size);
#endif
}

bool erebos::is_privileged() {
#ifdef WINDOWS
	return false; // TO-DO
#elif defined(LINUX)
	return geteuid() == 0;
#endif
}

int erebos::get_random_secure() {
#ifdef WINDOWS
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
#else
    return 0;
#endif
}


bool erebos::file::get_dir_file_list(const std::string& dir, std::vector<std::string>& output) {
#ifdef WINDOWS
	HANDLE           hFile;
	WIN32_FIND_DATA  wfd;
	TCHAR            path_ch[_MAX_PATH];

	// Compatible with Unix and Windows string format
	std::string path = dir;
	if (path.find("/") != std::string::npos)
		strutil::replace(path, '/', '\\');

	path.append("\\*");

	path_ch[path.size()] = '\0';
	std::copy(path.begin(), path.end(), path_ch);

	hFile = FindFirstFile(path_ch, &wfd);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	do {
		if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_NORMAL))
			output.emplace_back(wfd.cFileName);
	} while(FindNextFile(hFile, &wfd) != 0);

	CloseHandle(hFile);

	return true;

#elif defined(LINUX)
	DIR* handle = opendir(dir.c_str());

	if(!handle)
		return false;

	dirent *dir_entry;
	while((dir_entry = readdir(handle)))
		if(dir_entry->d_type == DT_REG)
			output.emplace_back(dir_entry->d_name);

	return closedir(handle) == 0;
#endif
}


bool erebos::file::get_dir_folder_list(const std::string& dir, std::vector<std::string>& output) {
#ifdef WINDOWS
	HANDLE           hFile;
	WIN32_FIND_DATA  wfd;
	TCHAR            path_ch[_MAX_PATH];

	// Compatible with Unix and Windows string format
	std::string path = dir;

	if (path.find("/") != std::string::npos)
		strutil::replace(path, '/', '\\');

	path.append("\\*");

	path_ch[path.size()] = '\0';
	std::copy(path.begin(), path.end(), static_cast<char*>(path_ch));

	hFile = FindFirstFile(path_ch, &wfd);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;

	do {
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			output.emplace_back(wfd.cFileName);
	} while(FindNextFile(hFile, &wfd) != 0);

	CloseHandle(hFile);
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
#ifdef WINDOWS
	DWORD dwAttributes = GetFileAttributes(foldername.c_str());

	return dwAttributes != INVALID_FILE_ATTRIBUTES &&
			(dwAttributes &  FILE_ATTRIBUTE_DIRECTORY);
#elif defined(LINUX)
	return !access(foldername.c_str(), F_OK);
#endif
}

#ifdef WINDOWS
std::uint32_t erebos::file::get_size(const std::string& filename) {
	HANDLE fd = CreateFile(filename.c_str(), GENERIC_READ, 0, nullptr,
							OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	DWORD size;
	GetFileSize(fd, &size);

	CloseHandle(fd);

	return size;
#elif defined(LINUX)
off_t erebos::file::get_size(const std::string& filename) {
	struct stat st;
	stat(filename.c_str(), &st);
	return st.st_size;
#endif
}
