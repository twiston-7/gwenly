#include <windows.h>
#include <d3d11.h>

#include "ui/ImGuiManager.h"
#include "setup/D3D11Device.h"

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

void ImGuiManager::SetupImGui(HWND& hwnd) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(D3D11Device::g_pd3dDevice, D3D11Device::g_pd3dDeviceContext);
}

void ImGuiManager::RenderContent(const std::function<void()>& renderFunc) {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (renderFunc)
        renderFunc();

    ImGui::Render();

    constexpr float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    D3D11Device::g_pd3dDeviceContext->OMSetRenderTargets(
        1,
        &D3D11Device::g_mainRenderTargetView,
        nullptr
    );

    D3D11Device::g_pd3dDeviceContext->ClearRenderTargetView(
        D3D11Device::g_mainRenderTargetView,
        clearColor
    );

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
