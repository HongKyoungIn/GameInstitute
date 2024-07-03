#include "RectangleRenderer.h"
#include "GameObject.h"

RectangleRenderer::RectangleRenderer(GameObject* owner)
    : Component(owner), mBrush(nullptr), mColor(D2D1::ColorF(D2D1::ColorF::Green)) { // �ʱ� ������ ������� ����
    mRectangle = D2D1::RectF(0.0f, 0.0f, 100.0f, 100.0f);  // �⺻ �簢�� ũ�� ����
}

RectangleRenderer::~RectangleRenderer() {
    if(mBrush) mBrush->Release();
}

void RectangleRenderer::SetColor(D2D1::ColorF color) {
    mColor = color; // ������ ����
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
