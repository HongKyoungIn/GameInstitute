#include "CircleRenderer.h"
#include "GameObject.h"

CircleRenderer::CircleRenderer(GameObject* owner)
    : Component(owner), mBrush(nullptr), mColor(D2D1::ColorF(D2D1::ColorF::Green)), mRadius(50.0f) { // �ʱ� ������ ������� �����ϰ� �������� ����
    mCenter = D2D1::Point2F(0.0f, 0.0f);  // ���� �߽��� �ʱ�ȭ
}

CircleRenderer::~CircleRenderer() {
    if (mBrush) mBrush->Release();
}

void CircleRenderer::SetColor(D2D1::ColorF color) {
    mColor = color; // ������ ����
    if (mBrush) {
        mBrush->SetColor(color);
    }
}

void CircleRenderer::SetRadius(float radius) {
    mRadius = radius; // �������� ����
}

void CircleRenderer::SetCenter(D2D1_POINT_2F center) {
    mCenter = center; // ���� �߽��� ����
}

void CircleRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
    if (!mBrush) {
        renderTarget->CreateSolidColorBrush(mColor, &mBrush);
    }

    D2D1_ELLIPSE ellipse = D2D1::Ellipse(mCenter, mRadius, mRadius);
    renderTarget->FillEllipse(ellipse, mBrush);
}
