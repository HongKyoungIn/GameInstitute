#include "RectangleRenderer.h"
#include "GameObject.h"

RectangleRenderer::RectangleRenderer(GameObject* owner)
    : Component(owner), mBrush(nullptr), mColor(D2D1::ColorF(D2D1::ColorF::Green)) { // 초기 색상을 녹색으로 설정
    mRectangle = D2D1::RectF(0.0f, 0.0f, 100.0f, 100.0f);  // 기본 사각형 크기 설정
}

RectangleRenderer::~RectangleRenderer() {
    if(mBrush) mBrush->Release();
}

void RectangleRenderer::SetColor(D2D1::ColorF color) {
    mColor = color; // 색상을 저장
    if(mBrush) {
        mBrush->SetColor(color);
    }
}

void RectangleRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
    if(!mBrush) {
        renderTarget->CreateSolidColorBrush(mColor, &mBrush);
    }
    renderTarget->FillRectangle(mRectangle, mBrush);
}
