
#ifdef _WIN32
#include <cstdint>
#include <windows.h>
#include <cstdarg>


void write_to_output(const uint8_t* packet, uintptr_t length) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD total = 0;
    while (total < length) {
        DWORD written = 0;
        if (!WriteFile(h, packet + total, length - total, &written, NULL)) {
            break;
        }
        total += written;
    }
}

#endif
