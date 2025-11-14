
#ifdef _WIN32

#include <windows.h>
#include "input.hpp"
#include <variant>

void game::InputListener::read(std::vector<std::variant<KeyboardEvent, MouseEvent>>& buffer) const {
	INPUT_RECORD record;
	DWORD count;
	while (PeekConsoleInput(handle, &record, 1, &count)) {
		ReadConsoleInput(handle, &record, 1, &count);
		if (record.EventType == KEY_EVENT) {
			buffer.emplace_back(KeyboardEvent(record.Event.KeyEvent.uChar.AsciiChar, record.Event.KeyEvent.bKeyDown));
		}
		if (record.EventType == MOUSE_EVENT) {
			MOUSE_EVENT_RECORD event = record.Event.MouseEvent;
			auto [x, y] = event.dwMousePosition;
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
			buffer.emplace_back(MouseEvent(buttons, Point(x, y)));
		}
	}
}

game::InputListener game::InputListener::create() {
	HANDLE stdin = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(stdin, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
	return InputListener(stdin);
}


#endif
