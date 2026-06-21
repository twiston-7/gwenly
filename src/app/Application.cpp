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

void Application::run() {
    std::wstring versionString = L"Latest League of Legends version: " +
        DataDragonService::GetLatestLeagueVersion()
        + L"\n-------------------------\n";

    OutputDebugStringW(
        versionString.c_str()
    );

    SummonerTimerInfo::Fetch();
    if (SummonerTimerInfo::enemySummonerData) {
        for (const auto& summonerData : SummonerTimerInfo::enemySummonerData.value()) {
            const auto cooldownSpellOne = DataDragonService::GetCooldownForSummonerSpell(summonerData.summonerSpellOne.displayName);
            const auto cooldownSpellTwo = DataDragonService::GetCooldownForSummonerSpell(summonerData.summonerSpellTwo.displayName);

            std::string debugString = "Champion: " + summonerData.championName +
                        "\nSummoner spell 1: " + summonerData.summonerSpellOne.displayName + " -- Cooldown: " + std::to_string(cooldownSpellOne) +
                        "\nSummoner spell 2: " + summonerData.summonerSpellTwo.displayName + " -- Cooldown: " + std::to_string(cooldownSpellTwo) +"\n";

            OutputDebugStringA(
                debugString.c_str()
            );
        }
    }

    if (!Window::CreateOverlayWindow())
        exit(1);

    HWND hwnd = Window::g_hWnd;

    D3D11Device::CreateDeviceD3D(hwnd);

    ImGuiManager::SetupImGui(hwnd);

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
