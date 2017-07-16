#include "input.h"
#include "platform_defs.h"

#ifdef WINDOWS
#define _WIN32_WINNT 0x0500
#include "windows.h"
#include "winuser.h"
#include "wincon.h"

#elif defined(LINUX)

#endif


int erebos::input::get_key(unsigned int delta) {

#ifdef WINDOWS


	HWND window = GetConsoleWindow();

	// Wait until a button is pressed
	while(true) {

		// Check if the console window is focused
		if(GetForegroundWindow() != window)
			continue;

		for (int i = 1; i < 255; ++i) {

			if(GetAsyncKeyState(i) & 0x07)
				return i;

		}

		Sleep(delta);
	}

#elif defined(LINUX)

	// TO-DO

#endif

}


bool erebos::input::fake_put(int key) {

#ifdef WINDOWS

	INPUT input;
	// We want to send a keyboard event
	input.type = 1;
	input.ki.wVk = key;
	input.ki.wScan = 0;
	input.ki.dwFlags = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = GetMessageExtraInfo();

	int res = SendInput(1, &input, sizeof(INPUT));

	return res != 0;

#elif defined(LINUX)

	// TO-DO

#endif

}

