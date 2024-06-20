#pragma once

#include <d2d1.h>

class D2DRenderer {
public:
    D2DRenderer();
    ~D2DRenderer();

    BOOL Initialize(HWND hWnd);
    void Uninitialize();
    void BeginDraw();
    void Clear(D2D1::ColorF color);
    void EndDraw();

private:
    ID2D1Factory* g_pD2DFactory;
    ID2D1HwndRenderTarget* g_pRenderTarget;
};
