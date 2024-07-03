#pragma once
#include "CommonInclude.h"
#include "Component.h"

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"windowscodecs.lib")


class Renderer {
public:
    Renderer();
    Renderer(GameObject* owner);
    virtual ~Renderer();

    static BOOL InitDirect2D(HWND hWnd);
    static void UninitDirect2D();
    static bool IsWindowFullscreen(HWND hWnd);
    static void EnterFullscreen(HWND hWnd);
    static void ExitFullscreen(HWND hWnd);

    ID2D1HwndRenderTarget* GetRenderTarget() const { return mRenderTarget; }
    ID2D1Factory* GetFactory() const { return mD2DFactory; }
    IWICImagingFactory* GetWICFactory() const { return mWICFactory; }

protected:
    static ID2D1Factory* mD2DFactory;
    static ID2D1HwndRenderTarget* mRenderTarget;
    static IWICImagingFactory* mWICFactory;
};