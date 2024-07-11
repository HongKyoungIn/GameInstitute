#include "VideoMemoryDisplay.h"
#include "Core.h"
#include "Defines.h"
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

//void VideoMemoryDisplay::Render(ID2D1HwndRenderTarget* renderTarget) {
//
//    D2D1_POINT_2F position = mOwner->GetTransform()->GetPosition();
//    D2D1_MATRIX_3X2_F worldTransform = mOwner->GetTransform()->GetWorldTransform();
//
//    renderTarget->SetTransform(worldTransform);
//    D2D1_RECT_F layoutRect = D2D1::RectF(position.x, position.y, position.x + 200, position.y + 50);
//    renderTarget->DrawTextW(mText.c_str(), mText.length(), mTextFormat, layoutRect, mBrush);
//}


void VideoMemoryDisplay::Render(ID2D1HwndRenderTarget* renderTarget) {
    D2D1_POINT_2F position = mOwner->GetTransform()->GetPosition();
    D2D1_MATRIX_3X2_F worldTransform = mOwner->GetTransform()->GetWorldTransform();

    renderTarget->SetTransform(worldTransform);

    // 텍스트 레이아웃을 생성하여 크기를 계산합니다.
    IDWriteTextLayout* pTextLayout = nullptr;
    Renderer* renderer = Core::GetRenderer();
    renderer->GetDWriteFactory()->CreateTextLayout(
        mText.c_str(),
        (UINT32)mText.length(),
        mTextFormat,
        200.0f, // 임의의 최대 너비
        50.0f,  // 임의의 최대 높이
        &pTextLayout
    );

    DWRITE_TEXT_METRICS textMetrics;
    pTextLayout->GetMetrics(&textMetrics);

    float halfWidth = textMetrics.width / 2.0f;
    float halfHeight = textMetrics.height / 2.0f;

    D2D1_RECT_F layoutRect = D2D1::RectF(position.x - halfWidth, position.y - halfHeight, position.x + halfWidth, position.y + halfHeight);
    renderTarget->DrawTextLayout(D2D1::Point2F(position.x - halfWidth, position.y - halfHeight), pTextLayout, mBrush);

    pTextLayout->Release();
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

    SAFE_RELEASE(pAdapter3);
    SAFE_RELEASE(pAdapter);
    SAFE_RELEASE(pDXGIFactory);

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