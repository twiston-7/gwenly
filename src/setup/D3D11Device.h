#ifndef GWENLY_D3D11Device_H
#define GWENLY_D3D11Device_H

#include <windows.h>
#include <d3d11.h>

class D3D11Device {
    static void CreateRenderTarget();
    static void CleanupRenderTarget();
public:
    static ID3D11Device* g_pd3dDevice;
    static ID3D11DeviceContext* g_pd3dDeviceContext;
    static IDXGISwapChain* g_pSwapChain;
    static ID3D11RenderTargetView* g_mainRenderTargetView;

    static bool CreateDeviceD3D(HWND hWnd);
    static void CleanupDeviceD3D();
};


#endif //GWENLY_D3D11Device_H
