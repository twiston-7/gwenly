cmake_minimum_required(VERSION 3.20)
project(Gwenly)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Gwenly WIN32
        src/main.cpp
        src/setup/D3D11Device.cpp
        src/setup/D3D11Device.h
        src/ui/ImGuiManager.cpp
        src/ui/ImGuiManager.h
        src/setup/Window.cpp
        src/setup/Window.h
        src/api/gameclient/LeagueGameClientApi.cpp
        src/api/gameclient/LeagueGameClientApi.h
        src/app/Application.cpp
        src/app/Application.h
        src/core/SummonerTimerInfo.cpp
        src/core/SummonerTimerInfo.h
        src/data/ChampionSummonerSpellData.h
        src/api/gameclient/data/GameClientDataModels.h
        src/data/GameVersion.h
        src/api/BasicRequest.cpp
        src/api/BasicRequest.h
        src/api/datadragon/DataDragonService.cpp
        src/api/datadragon/DataDragonService.h
        src/data/Constants.h
        src/api/gameclient/data/RuneInfo.h
        src/api/gameclient/data/Runes.h
        src/api/gameclient/data/Scores.h
        src/api/gameclient/data/Item.h
        src/api/gameclient/data/Player.h
        src/api/gameclient/data/SummonerSpells.h
        src/render/SummonerSpellTrackerFrame.cpp
        src/render/SummonerSpellTrackerFrame.h
        src/ui/TextureManager.cpp
        src/ui/TextureManager.h
        src/api/datadragon/data/SummonerSpellInfo.h
        src/api/datadragon/data/SummonerSpellInfo.h
)

target_compile_definitions(Gwenly PRIVATE UNICODE _UNICODE)

target_include_directories(Gwenly PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Gwenly PRIVATE
    d3d11
    d3dcompiler
    dwmapi
    winhttp
    nlohmann_json::nlohmann_json
    imgui::imgui
)