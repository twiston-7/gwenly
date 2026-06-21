#include "Application.h"

#include <windows.h>
#include <imgui.h>
#include <winuser.h>

#include "../core/SummonerTimerInfo.h"
#include "api/datadragon/DataDragonService.h"
#include "render/SummonerSpellTrackerFrame.h"
#include "setup/D3D11Device.h"
#include "setup/Window.h"
#include "ui/ImGuiManager.h"
#include "ui/TextureManager.h"

void Application::run() {
    if (!Window::CreateOverlayWindow())
        exit(1);

    HWND hwnd = Window::g_hWnd;

    D3D11Device::CreateDeviceD3D(hwnd);

    ImGuiManager::SetupImGui(hwnd);

    std::wstring versionString = L"Latest League of Legends version: " +
    DataDragonService::GetLatestLeagueVersion()
    + L"\n-------------------------\n";

    OutputDebugStringW(
        versionString.c_str()
    );

    SummonerTimerInfo::Fetch();
    if (SummonerTimerInfo::enemySummonerData) {
        for (const auto& summonerData : SummonerTimerInfo::enemySummonerData.value()) {
            std::string imageBytes = DataDragonService::GetSummonerSpellImageBytes(summonerData.summonerSpellOne.displayName);
            bool loaded = TextureManager::LoadFromMemory(
                summonerData.summonerSpellTwo.displayName,
                reinterpret_cast<const unsigned char*>(imageBytes.data()),
                imageBytes.size()
            );

            if (!loaded) {
                OutputDebugStringW(L"Failed to load texture from memory.\n");
            }

            imageBytes = DataDragonService::GetSummonerSpellImageBytes(summonerData.summonerSpellTwo.displayName);
            loaded = TextureManager::LoadFromMemory(
                summonerData.summonerSpellTwo.displayName,
                reinterpret_cast<const unsigned char*>(imageBytes.data()),
                imageBytes.size()
            );

            if (!loaded) {
                OutputDebugStringW(L"Failed to load texture from memory.\n");
            }
        }
    }

    MSG msg = {};

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGuiManager::RenderContent(SummonerSpellTrackerFrame::Render);

        D3D11Device::g_pSwapChain->Present(1, 0);
    }
}
