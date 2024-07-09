#include "VideoMemoryDisplay.h"
#include "Core.h"
#include <dxgi1_4.h>
#include <sstream>
#include <iomanip>

VideoMemoryDisplay::VideoMemoryDisplay(GameObject* owner) : Component(owner) {
    Renderer* renderer = Core::GetRenderer();
    mTextFormat = renderer->GetTextFormat();
    mBrush = renderer->GetBrush();
}

VideoMemoryDisplay::~VideoMemoryDisplay() { }

void VideoMemoryDisplay::Update() {
    SIZE_T usedVRAM = GetUsedVRAM();
    SIZE_T totalVRAM = GetTotalVRAM();
    std::wstringstream ss;
    ss << L"VRAM: " << usedVRAM << L"MB / " << totalVRAM << L"MB";
    mText = ss.str();
}

void VideoMemoryDisplay::Render(ID2D1HwndRenderTarget* renderTarget) {
    D2D1_POINT_2F position = mOwner->GetTransform()->GetPosition();
    D2D1_RECT_F layoutRect = D2D1::RectF(position.x, position.y, position.x + 200, position.y + 50);
    renderTarget->DrawTextW(mText.c_str(), mText.length(), mTextFormat, layoutRect, mBrush);
}

SIZE_T VideoMemoryDisplay::GetUsedVRAM() {
    IDXGIAdapter* pAdapter = nullptr;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIFactory* pDXGIFactory;

    CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);
    pDXGIFactory->EnumAdapters(0, &pAdapter);
    pAdapter->GetDesc(&adapterDesc);

    // IDXGIAdapter3로 업캐스팅하여 QueryVideoMemoryInfo 메서드를 사용
    IDXGIAdapter3* pAdapter3 = nullptr;
    pAdapter->QueryInterface(__uuidof(IDXGIAdapter3), (void**)&pAdapter3);

    DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
    pAdapter3->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
    SIZE_T usedVRAM = videoMemoryInfo.CurrentUsage / 1024 / 1024; // MB 단위로 변환

    pAdapter3->Release();
    pAdapter->Release();
    pDXGIFactory->Release();

    return usedVRAM;
}

SIZE_T VideoMemoryDisplay::GetTotalVRAM() {
    IDXGIAdapter* pAdapter = nullptr;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIFactory* pDXGIFactory;

    CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);
    pDXGIFactory->EnumAdapters(0, &pAdapter);
    pAdapter->GetDesc(&adapterDesc);

    SIZE_T totalVRAM = adapterDesc.DedicatedVideoMemory / (1024 * 1024); // MB 단위로 변환

    pAdapter->Release();
    pDXGIFactory->Release();

    return totalVRAM;
}