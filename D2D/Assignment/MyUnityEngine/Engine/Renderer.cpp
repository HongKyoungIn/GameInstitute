#include "Renderer.h"
#include <comdef.h>

ID2D1Factory* Renderer::mD2DFactory = nullptr;
ID2D1HwndRenderTarget* Renderer::mRenderTarget = nullptr;
IWICImagingFactory* Renderer::mWICFactory = nullptr;

Renderer::Renderer()
    : Component() { }

Renderer::Renderer(GameObject* owner)
    : Component(owner) { }

Renderer::~Renderer() {
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

    return TRUE;
}

void Renderer::UninitDirect2D() {
    if(mRenderTarget) {
        mRenderTarget->Release();
        mRenderTarget = nullptr;
    }
    if(mD2DFactory) {
        mD2DFactory->Release();
        mD2DFactory = nullptr;
    }
    if(mWICFactory) {
        mWICFactory->Release();
        mD2DFactory = nullptr;
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

void Renderer::Render(ID2D1HwndRenderTarget* renderTarget) {
    // 기본 렌더링 작업을 정의합니다. 이를 상속받는 클래스에서 오버라이드해야 합니다.
    // 기본 구현은 빈 상태로 둡니다.
}