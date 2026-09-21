cmake_minimum_required(VERSION 3.20)
project(Gwenly)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE GWENLY_SOURCES CONFIGURE_DEPENDS src/*.cpp)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Gwenly WIN32 ${GWENLY_SOURCES})

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