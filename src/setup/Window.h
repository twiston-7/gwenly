#ifndef GWENLY_WINDOW_H
#define GWENLY_WINDOW_H

#include <windows.h>

class Window {
public:
    static HWND g_hWnd;
    static HINSTANCE g_hInstance;

    static bool CreateOverlayWindow();
    static void Cleanup(int exitCode = 0);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    static void RegisterWindowClass();
};

#endif // GWENLY_WINDOW_H