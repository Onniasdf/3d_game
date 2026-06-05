
#ifdef _WIN32
#include <cstdint>
#define NOMINMAX
#include <windows.h>
#include <cstdarg>


void write_to_output(const uint8_t* packet, const uintptr_t length) {
	const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD total = 0;
    while (total < length) {
        DWORD written = 0;
        if (!WriteFile(h, packet + total, length - total, &written, nullptr)) {
            break;
        }
        total += written;
    }
}

#endif
