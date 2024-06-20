#include "pch.h"
#include "D2DRenderer.h"

D2DRenderer::D2DRenderer() : g_pD2DFactory(nullptr), g_pRenderTarget(nullptr) { }

D2DRenderer::~D2DRenderer() {
    Uninitialize();
}

BOOL D2DRenderer::Initialize(HWND hWnd) {
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
    if(FAILED(hr)) {
        return FALSE;
    }

    RECT rc;
    GetClientRect(hWnd, &rc);
    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    hr = g_pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hWnd, size),
        &g_pRenderTarget);

    if(FAILED(hr)) {
        return FALSE;
    }

    return TRUE;
}

void D2DRenderer::Uninitialize() {
    if(g_pRenderTarget) {
        g_pRenderTarget->Release();
        g_pRenderTarget = nullptr;
    }
    if(g_pD2DFactory) {
        g_pD2DFactory->Release();
        g_pD2DFactory = nullptr;
    }
}

void D2DRenderer::BeginDraw() {
    g_pRenderTarget->BeginDraw();
}

void D2DRenderer::EndDraw() {
    g_pRenderTarget->EndDraw();
}

void D2DRenderer::Clear(D2D1::ColorF color) {
    g_pRenderTarget->Clear(color);
}
