#include "SDL.h"
#include "Game.h"
#include <memory>

#ifdef  _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


int main(int argc, char** argv) {
    try {
#ifdef _WIN32
        auto handle = GetConsoleWindow();
        ShowWindow(handle, SW_HIDE);
#endif
        return Game{}.Run();
    }
    catch (const std::exception& e) {
#ifdef _WIN32
        char buffer[512];
        sprintf_s(buffer, "Error message: %s\n", e.what());
        OutputDebugStringA(buffer);
#endif
   }
    catch (...) {
#ifdef _WIN32
        OutputDebugStringW(L"Error message: Unknown error\n");
#endif
    }
}