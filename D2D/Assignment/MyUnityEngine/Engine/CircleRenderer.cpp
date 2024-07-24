#include "CircleRenderer.h"
#include "GameObject.h"

CircleRenderer::CircleRenderer(GameObject* owner)
    : Component(owner), mBrush(nullptr), mColor(D2D1::ColorF(D2D1::ColorF::Green)), mRadius(50.0f) { // 초기 색상을 녹색으로 설정하고 반지름을 설정
    mCenter = D2D1::Point2F(0.0f, 0.0f);  // 원의 중심을 초기화
}

CircleRenderer::~CircleRenderer() {
    if (mBrush) mBrush->Release();
}

void CircleRenderer::SetColor(D2D1::ColorF color) {
    mColor = color; // 색상을 저장
    if (mBrush) {
        mBrush->SetColor(color);
    }
}

void CircleRenderer::SetRadius(float radius) {
    mRadius = radius; // 반지름을 설정
}

void CircleRenderer::SetCenter(D2D1_POINT_2F center) {
    mCenter = center; // 원의 중심을 설정
}

void CircleRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
    if (!mBrush) {
        renderTarget->CreateSolidColorBrush(mColor, &mBrush);
    }

    D2D1_ELLIPSE ellipse = D2D1::Ellipse(mCenter, mRadius, mRadius);
    renderTarget->FillEllipse(ellipse, mBrush);
}
