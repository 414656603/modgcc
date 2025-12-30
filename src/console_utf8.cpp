#include "console_utf8.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace demo {

void InitConsoleUtf8()
{
#ifdef _WIN32
    // Prefer UTF-8 when attached to a real console.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

} // namespace demo
