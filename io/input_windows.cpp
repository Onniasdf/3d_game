
#ifdef _WIN32

#define NOMINMAX
#include <windows.h>
#include "input.hpp"
#include <variant>
#include "../datastructures/vector3.hpp"
#include <vector>
#include <algorithm>
#include <cstdint>

constexpr auto BUFFER_SIZE = 10;

void io::InputListener::read(std::vector<std::variant<KeyboardEvent, MouseButtons, Point, SpecialKey>>& buffer) const {
	INPUT_RECORD records[BUFFER_SIZE];
	DWORD count;
	GetNumberOfConsoleInputEvents(handle, &count);
	if (count == 0) return;
	ReadConsoleInput(handle, records, std::min<DWORD>(BUFFER_SIZE, count), &count);
	for (int32_t i = 0; i < count; i++) {
		INPUT_RECORD record = records[i];
		if (record.EventType == KEY_EVENT) {
			if (record.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
				buffer.emplace_back(ESCAPE);
				continue;
			}
			buffer.emplace_back(KeyboardEvent(record.Event.KeyEvent.uChar.AsciiChar, record.Event.KeyEvent.bKeyDown));
		}
		if (record.EventType == MOUSE_EVENT) {
			MOUSE_EVENT_RECORD event = record.Event.MouseEvent;
			MouseButtons buttons = {};
			if (event.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
				buttons |= LEFT;
			}
			if (event.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
				buttons |= RIGHT;
			}
			if (event.dwButtonState & FROM_LEFT_2ND_BUTTON_PRESSED) {
				buttons |= MIDDLE;
			}
			if (event.dwButtonState & FROM_LEFT_3RD_BUTTON_PRESSED) {
				buttons |= EXTRA1;
			}
			if (event.dwButtonState & FROM_LEFT_4TH_BUTTON_PRESSED) {
				buttons |= EXTRA2;
			}
			buffer.emplace_back(buttons);
			auto [x, y] = event.dwMousePosition;
			buffer.emplace_back(Point(x, y));
			}
		}
}

io::InputListener io::InputListener::create() {
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
	return InputListener(handle);
}

io::InputListener::~InputListener() {

}



#endif
