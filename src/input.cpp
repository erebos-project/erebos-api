#include "input.h"

#ifdef WINDOWS
#define _WIN32_WINNT 0x0500
#include "windows.h"
#include "winuser.h"
#include "wincon.h"
#elif defined(LINUX)
#include <sys/time.h>
#include <linux/uinput.h>
#include <linux/limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <thread>
#include <chrono>

#define EVENT_BYPATH "/dev/input/by-path/"
#define NEED_MATCH "-event-kbd"
#define NEED_MATCH_COUNT 10
#define COPY_INPUT_EVENT(from_stream,dest) \
	 for(unsigned i=0;i<sizeof(struct input_event);i++) \
		  ((char*)&dest)[i] = fgetc(from_stream)
#endif

using eikey = erebos::input::Key;

#ifdef LINUX
//https://gist.github.com/StefanoBelli/c12965643c86044719c75fcaaa7d0178
static int get_keyboard_evpath_s(char* target) {
	 DIR* evbp_dir = opendir(EVENT_BYPATH);
	 if(!evbp_dir)
		  return -1;

	 struct dirent *entry;

	 while((entry=readdir(evbp_dir))) {
		  if(entry->d_type == DT_LNK) {
				if(!strncmp(entry->d_name + (strlen(entry->d_name) - NEED_MATCH_COUNT),
							NEED_MATCH,NEED_MATCH_COUNT))
					 break;
		  }
	 }

	 char local_target[PATH_MAX];
	 int evbpfd = dirfd(evbp_dir);

	 if(readlinkat(evbpfd,entry->d_name,local_target,sizeof(entry->d_name)) == -1)
		  return -1;

	 char current_workdir[PATH_MAX];
	 if(!getcwd(current_workdir,PATH_MAX))
		  return -1;

	 if(fchdir(evbpfd) < 0)
		  return -1;

	 if(!realpath(local_target,target))
		  return -1;

	 if(closedir(evbp_dir) < 0)
		  return -1;

	 if(chdir(current_workdir) < 0)
		  return -1;

	 return 0;
}

FILE* erebos::input::getev_physical_keyboard() {
	 char path[PATH_MAX];
	 int ret = get_keyboard_evpath_s(path);

	 return ret ? nullptr : fopen(path,"r");
}

int erebos::input::new_virtual_kb_device(const char* name, const bool& after_wait,
		const u16& bus_type, const u16& vendor,
		const u16& product, const u16& version) {
	 int fd=open("/dev/uinput",O_WRONLY | O_NONBLOCK);
	 if(fd < 0)
		  return -1;

	 if(ioctl(fd,UI_SET_EVBIT,EV_KEY) < 0)
		  return -1;

	 for(u16 i=0;i<256;i++)
		  if(ioctl(fd,UI_SET_KEYBIT,i) < 0)
				return -1;

	 //prepare new device
	 struct uinput_user_dev keyboard;
	 memset(&keyboard,0,sizeof(struct uinput_user_dev));
	 keyboard.id.bustype = bus_type;
	 keyboard.id.vendor = vendor;
	 keyboard.id.product = product;
	 keyboard.id.version = version;
	 snprintf(keyboard.name,UINPUT_MAX_NAME_SIZE,"%s",name);

	 if(write(fd,&keyboard,sizeof(struct uinput_user_dev)) < 0)
		  return -1;

	 //create by written data
	 if(ioctl(fd,UI_DEV_CREATE) < 0)
		  return -1;

	 if(after_wait)
		  std::this_thread::sleep_for(std::chrono::milliseconds(500));

	 return fd;
}

bool erebos::input::destroy_virtual_kb_device(const int& devfd) {
	 if(ioctl(devfd,UI_DEV_DESTROY) < 0)
		  return false;

	 return close(devfd) >= 0;
}
#endif


#ifdef WINDOWS
eikey erebos::input::get_key(const unsigned& delta) {

	HWND window = GetConsoleWindow();

	// Wait until a button is pressed
	while(true) {

		// Check if the console window is focused
		if(GetForegroundWindow() != window)
			continue;

		for (int i = 1; i < 255; ++i) {

			if(GetAsyncKeyState(i) & 0x07)
				return static_cast<Key>(i);

		}

		Sleep(delta);
	}

	//unreachable code
	//return -1;
}
#elif defined(LINUX)
eikey erebos::input::get_key(FILE *physkb) {
	 struct input_event current;

	 while(true) {
		  COPY_INPUT_EVENT(physkb,current);

		  if(current.type == EV_KEY && current.value == 1)
				return static_cast<Key>(current.code);
	 }
	 //unreachable code
	 //return -1;
}
#endif

#ifdef WINDOWS
bool erebos::input::fake_put(const Key& key) {

	INPUT input;
	// We want to send a keyboard event
	input.type = 1;
	input.ki.wVk = static_cast<int>(key);
	input.ki.wScan = 0;
	input.ki.dwFlags = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = GetMessageExtraInfo();

	int res = SendInput(1, &input, sizeof(INPUT));

	return res != 0;
}
#elif defined(LINUX)
bool erebos::input::fake_put(const int& devfd, const Key& key,
		const KeyPressType& type) {
	 static struct input_event event;

	 gettimeofday(&event.time,NULL);
	 event.type = EV_KEY;
	 event.code = static_cast<u16>(key);
	 event.value = static_cast<u16>(type);

	 if(write(devfd,&event,sizeof(struct input_event)) < 0)
		  return false;

	 event.type = EV_SYN;
	 event.code = SYN_REPORT;
	 event.value = 0;

	 return write(devfd,&event,sizeof(struct input_event)) >= 0;
}
#endif


