#ifndef EREBOS_INPUT_H
#define EREBOS_INPUT_H

#include "platform_defs.h"

#ifdef LINUX
#include <linux/input-event-codes.h>
#include <string>
#include <cstdio>
#define INPUT_KEYTYPE u16
#elif defined(WINDOWS)
#define INPUT_KEYTYPE int
#endif

namespace erebos {

	/*!
	 * @brief input handling
	 */
	namespace input {
		using u16 = unsigned short;

		/*!
		 * @brief common virtual key codes
		 */
		enum class Key : INPUT_KEYTYPE {
#if defined(WINDOWS)
			KEY_WINAPI_ERROR = -1,
			KEY_MOUSE_LEFT = 1,
			KEY_MOUSE_RIGHT = 2,
			KEY_CANCEL = 3,
			KEY_MOUSE_MIDDLE = 4,
			KEY_BACKSPACE = 8,
			KEY_TAB = 9,
			KEY_CLEAR = 12,
			KEY_ENTER = 13,
			KEY_SHIFT = 16,
			KEY_CONTROL = 17,
			KEY_ALT = 18,
			KEY_PAUSE = 19,
			KEY_CAPSLOCK = 20,
			KEY_ESCAPE = 0x1B,
			KEY_SPACE = 32,
			KEY_PAGEUP = 33,
			KEY_PAGEDOWN = 34,
			KEY_END = 35,
			KEY_HOME = 36,
			KEY_LEFT = 37,
			KEY_UP = 38,
			KEY_RIGHT = 39,
			KEY_DOWN = 40,
			KEY_SELECT = 41,
			KEY_PRINT = 42,
			KEY_EXECUTE = 43,
			KEY_SNAPSHOT = 44,
			KEY_INSERT = 45,
			KEY_DELETE = 46,
			KEY_HELP = 47,
			KEY_LWIN = 0x5B,
			KEY_RWIN = 0x5C,
			KEY_APPS = 0x5D,
			KEY_SLEEP = 0x5F,
			KEY_NUMPAD0 = 0x60,
			KEY_NUMPAD1 = 0x61,
			KEY_NUMPAD2 = 0x62,
			KEY_NUMPAD3 = 0x63,
			KEY_NUMPAD4 = 0x64,
			KEY_NUMPAD5 = 0x65,
			KEY_NUMPAD6 = 0x66,
			KEY_NUMPAD7 = 0x67,
			KEY_NUMPAD8 = 0x68,
			KEY_NUMPAD9 = 0x69,
			KEY_MULTIPLY = 0x6A,
			KEY_ADD = 0x6B,
			KEY_SEPARATOR = 0x6C,
			KEY_SUBTRACT = 0x6D,
			KEY_DECIMAL = 0x6E,
			KEY_DIVIDE = 0x6F,
			KEY_F1 = 0x70,
			KEY_F2 = 0x71,
			KEY_F3 = 0x72,
			KEY_F4 = 0x73,
			KEY_F5 = 0x74,
			KEY_F6 = 0x75,
			KEY_F7 = 0x76,
			KEY_F8 = 0x77,
			KEY_F9 = 0x78,
			KEY_F10 = 0x79,
			KEY_F11 = 0x7A,
			KEY_F12 = 0x7B,
			KEY_F13 = 0x7C,
			KEY_F14 = 0x7D,
			KEY_F15 = 0x7E,
			KEY_F16 = 0x7F,
			KEY_F17 = 0x80,
			KEY_F18 = 0x81,
			KEY_F19 = 0x82,
			KEY_F20 = 0x83,
			KEY_F21 = 0x84,
			KEY_F22 = 0x85,
			KEY_F23 = 0x86,
			KEY_F24 = 0x87,
			KEY_NUMLOCK = 0x90,
			KEY_SCROLL = 0x91,
			KEY_SHIFT_LEFT = 0xA0,
			KEY_SHIFT_RIGHT = 0xA1,
			KEY_CONTROL_LEFT = 0xA2,
			KEY_CONTROL_RIGHT = 0xA3,
			KEY_ALT_LEFT = 0xA4,
			KEY_ALT_RIGHT = 0xA5,
			KEY_ATTN = 0xF6,
			KEY_CRSEL = 0xF7,
			KEY_EXSEL = 0xF8,
			KEY_EREOF = 0xF9,
			KEY_PLAY = 0xFA,
			KEY_ZOOM = 0xFB,
			KEY_NONAME = 0xFC
#endif
		};

#if defined(WINDOWS)
		/*!
		 * @brief wait until a key is pressed
		 * @param delta : the milliseconds to wait for updating (default is 66)
		 * @return the key that was pressed
		 */
		ERAPI Key get_key(const unsigned& delta = 66);

		/*!
		 * @brief send fake input to the system
		 * @param key : the key to fake
		 * @return true in case of success
		 */
		ERAPI bool fake_put(const Key& key);
#elif defined(LINUX)
        enum class KeyPressType : u16 {
			KEY_RELEASE = 0,
			KEY_PRESS = 1
		};

		FILE* getev_physical_keyboard();
		Key get_key(FILE* physkb);

		int new_virtual_kb_device(const char* name,
								  const u16& bus_type = 0x03, //USB
								  const u16& vendor = 0x01,
								  const u16& product = 0x02,
								  const u16& version = 0x03);

		bool fake_put(const int& devfd, const Key& key, const KeyPressType& type);
		bool destroy_virtual_kb_device(const int& devfd);

		//We want to use only keys specified in Key enum
		bool fake_put(int,int) = delete;
		bool fake_put(int,int,KeyPressType) = delete;

		//Just a shortcut...
		inline bool fake_put(const int& devfd, const Key& key) {
			if(!fake_put(devfd,key,KeyPressType::KEY_PRESS))
				return false;

			return fake_put(devfd,key,KeyPressType::KEY_RELEASE);
		}
#endif

	}
}


#endif
