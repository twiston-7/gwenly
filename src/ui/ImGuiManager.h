#ifndef GWENLY_IMGUISETUP_H
#define GWENLY_IMGUISETUP_H
#include <functional>
#include <windef.h>


class ImGuiManager {
public:
    static void SetupImGui(HWND &hwnd);

    static void RenderContent(const std::function<void()>& renderFunc);
};


#endif //GWENLY_IMGUISETUP_H
