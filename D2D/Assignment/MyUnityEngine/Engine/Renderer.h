#pragma once
#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>
#include <dxgi1_4.h>
#include <iostream>
#include "GameObject.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dwrite.lib")

class Renderer {
public:
    Renderer();
    Renderer(GameObject* owner);
    ~Renderer();

    BOOL InitDirect2D(HWND hWnd);
    void UninitDirect2D();
    bool IsWindowFullscreen(HWND hWnd);
    void EnterFullscreen(HWND hWnd);
    void ExitFullscreen(HWND hWnd);

    size_t GetUsedVRAM();
    size_t GetTotalVRAM();

    IDWriteTextFormat* GetTextFormat() const { return mTextFormat; }
    ID2D1SolidColorBrush* GetBrush() const { return mBrush; }
    ID2D1HwndRenderTarget* GetRenderTarget() const { return mRenderTarget; }
    ID2D1Factory* GetFactory() const { return mD2DFactory; }
    IWICImagingFactory* GetWICFactory() const { return mWICFactory; }
    IDXGIFactory* GetDXGIFactory() const { return mDXGIFactory; }
    IDWriteFactory* GetDWriteFactory() const { return mDWriteFactory; }

    

private:
    static ID2D1Factory* mD2DFactory;
    static ID2D1HwndRenderTarget* mRenderTarget;
    static IWICImagingFactory* mWICFactory;
    static IDXGIFactory* mDXGIFactory;
    static IDXGIAdapter3* mDXGIAdapter;
    static IDWriteFactory* mDWriteFactory;
    static IDWriteTextFormat* mTextFormat;
    static ID2D1SolidColorBrush* mBrush;
};
