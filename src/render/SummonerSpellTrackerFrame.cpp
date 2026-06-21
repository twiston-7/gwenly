#include "SummonerSpellTrackerFrame.h"


#include <imgui.h>
#include <windows.h>

int SummonerSpellTrackerFrame::screenWidth = GetSystemMetrics(SM_CXSCREEN);
int SummonerSpellTrackerFrame::screenHeight = GetSystemMetrics(SM_CYSCREEN);

void SummonerSpellTrackerFrame::Render() {
    const float posX = static_cast<float>(screenWidth);
    const float posY = screenHeight * 0.30f;

    ImGui::SetNextWindowPos(
        ImVec2(posX, posY),
        ImGuiCond_Always,
        ImVec2(1.0f, 1.0f)
    );

    ImGui::SetNextWindowSize(ImVec2(-1, -1), ImGuiCond_Always);

    ImGui::SetNextWindowBgAlpha(0.35f);

    ImGui::Begin("Gwenly", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoResize);

    ImGui::SetWindowFontScale(2.0f);
    ImGui::TextColored(ImVec4(1, 1, 1, 1), "Hello, jungle!");

    ImGui::End();
}
