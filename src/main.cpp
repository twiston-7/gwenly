#include "app/Application.h"

#include <windows.h>

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    Application::run();

    return 0;
}
