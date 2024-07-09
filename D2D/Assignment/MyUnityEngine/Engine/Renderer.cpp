#include "Renderer.h"
#include <comdef.h>
#include "ResourceManager.h"

ID2D1Factory* Renderer::mD2DFactory = nullptr;
ID2D1HwndRenderTarget* Renderer::mRenderTarget = nullptr;
IWICImagingFactory* Renderer::mWICFactory = nullptr;
IDWriteFactory* Renderer::mDWriteFactory = nullptr;
IDWriteTextFormat* Renderer::mTextFormat = nullptr;
ID2D1SolidColorBrush* Renderer::mBrush = nullptr;
IDXGIFactory* Renderer::mDXGIFactory = nullptr;
IDXGIAdapter3* Renderer::mDXGIAdapter = nullptr;

Renderer::Renderer() { }

Renderer::Renderer(GameObject* owner) { }

Renderer::~Renderer() {
    std::cout << "Renderer destructor called" << std::endl;
    UninitDirect2D();
}

BOOL Renderer::InitDirect2D(HWND hWnd) {
    HRESULT hr = S_OK;

    hr = CoInitialize(NULL);
    if(FAILED(hr)) {
        return FALSE;
    }

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
    if(FAILED(hr)) {
        return FALSE;
    }

    RECT rc;
    GetClientRect(hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    hr = mD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hWnd, size),
        &mRenderTarget);

    if(FAILED(hr)) {
        return FALSE;
    }

    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&mWICFactory));

    if(FAILED(hr))
        return FALSE;

    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(mDWriteFactory),
        reinterpret_cast<IUnknown**>(&mDWriteFactory));
    if(FAILED(hr))
        return FALSE;

    hr = mDWriteFactory->CreateTextFormat(
        L"Arial", // FontName
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        15.0f, // Font Size
        L"", // locale
        &mTextFormat);
    if(FAILED(hr))
        return FALSE;

    hr = mRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &mBrush);
    if(FAILED(hr))
        return FALSE;

    hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&mDXGIFactory);
    if(FAILED(hr))
        return FALSE;

    hr = mDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&mDXGIAdapter));
    if(FAILED(hr))
        return FALSE;

    return TRUE;
}

void Renderer::UninitDirect2D() {
    std::cout << "Uninitializing Direct2D" << std::endl;

    if(mRenderTarget) {
        mRenderTarget->Release();
        mRenderTarget = nullptr;
    }
    if(mBrush) {
        mBrush->Release();
        mBrush = nullptr;
    }
    if(mTextFormat) {
        mTextFormat->Release();
        mTextFormat = nullptr;
    }
    if(mWICFactory) {
        mWICFactory->Release();
        mWICFactory = nullptr;
    }
    if(mD2DFactory) {
        mD2DFactory->Release();
        mD2DFactory = nullptr;
    }
    if(mDWriteFactory) {
        mDWriteFactory->Release();
        mDWriteFactory = nullptr;
    }
    if(mDXGIFactory) {
        mDXGIFactory->Release();
        mDXGIFactory = nullptr;
    }
    if(mDXGIAdapter) {
        mDXGIAdapter->Release();
        mDXGIAdapter = nullptr;
    }

    CoUninitialize();
}

bool Renderer::IsWindowFullscreen(HWND hWnd) {
    LONG style = GetWindowLong(hWnd, GWL_STYLE);
    return ((style & WS_POPUP) == WS_POPUP);
}

void Renderer::EnterFullscreen(HWND hWnd) {
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

    MONITORINFO monitorInfo = { sizeof(monitorInfo) };
    GetMonitorInfo(hMonitor, &monitorInfo);

    SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

    SetWindowPos(hWnd, HWND_TOP, monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
        monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
        monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
        SWP_NOZORDER | SWP_FRAMECHANGED);
}

void Renderer::ExitFullscreen(HWND hWnd) {
    SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);

    SetWindowPos(hWnd, HWND_TOP, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

size_t Renderer::GetUsedVRAM() {
    DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
    mDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
    return videoMemoryInfo.CurrentUsage / 1024 / 1024; // Convert to MB
}

size_t Renderer::GetTotalVRAM() {
    DXGI_ADAPTER_DESC desc;
    mDXGIAdapter->GetDesc(&desc);
    return desc.DedicatedVideoMemory / 1024 / 1024; // Convert to MB
}
