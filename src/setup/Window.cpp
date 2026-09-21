#include "Window.h"

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <tchar.h>

#include "setup/D3D11Device.h"

HWND Window::g_hWnd = nullptr;
HINSTANCE Window::g_hInstance = nullptr;

constexpr int SHUTDOWN_HOTKEY_ID = 1;

static const TCHAR* WINDOW_CLASS_NAME = _T("JungleOverlayClass");
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

HHOOK g_hKeyboardHook = nullptr;
constexpr SHORT SHORT_BIT_15 = 0x8000;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        auto* kb = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        if (wParam == WM_KEYDOWN &&
            kb->vkCode == VK_F12 &&
            GetAsyncKeyState(VK_CONTROL) & SHORT_BIT_15
        ) {
            PostMessage(Window::g_hWnd, WM_HOTKEY, SHUTDOWN_HOTKEY_ID, 0);
        }
    }
    return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}

void Window::RegisterWindowClass()
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L,
                      g_hInstance, nullptr, nullptr, nullptr, nullptr,
                      WINDOW_CLASS_NAME, nullptr };

    RegisterClassEx(&wc);
}

bool Window::CreateOverlayWindow()
{
    g_hInstance = GetModuleHandle(nullptr);

    RegisterWindowClass();

    const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    const int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    g_hWnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
        WINDOW_CLASS_NAME,
        _T("Gwenly"),
        WS_POPUP,
        0, 0, screenWidth, screenHeight,
        nullptr, nullptr,
        g_hInstance,
        nullptr
    );

    if (!g_hWnd)
        return false;

    SetLayeredWindowAttributes(g_hWnd, RGB(0, 0, 0), 255, LWA_COLORKEY);

    const LONG exStyle = GetWindowLong(g_hWnd, GWL_EXSTYLE);
    SetWindowLong(g_hWnd, GWL_EXSTYLE, exStyle | WS_EX_TRANSPARENT);

    ShowWindow(g_hWnd, SW_SHOW);
    UpdateWindow(g_hWnd);

    g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, g_hInstance, 0);
    return true;
}

void Window::Cleanup(const int exitCode)
{
    static bool cleaningUp = false;
    if (cleaningUp)
        return;
    cleaningUp = true;

    PostQuitMessage(exitCode);

    if (g_hWnd)
    {
        DestroyWindow(g_hWnd);
        g_hWnd = nullptr;
    }

    if (g_hKeyboardHook) { UnhookWindowsHookEx(g_hKeyboardHook); }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    D3D11Device::CleanupDeviceD3D();
    UnregisterClass(WINDOW_CLASS_NAME, g_hInstance);
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
        case WM_CLOSE:
        case WM_QUERYENDSESSION:
        case WM_ENDSESSION:
        case WM_DESTROY:
            Cleanup();
            return 0;
        case WM_HOTKEY:
            if (wParam == SHUTDOWN_HOTKEY_ID) {
                Cleanup();
                return 0;
            }
            break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
