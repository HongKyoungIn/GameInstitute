#pragma once

#include "Component.h"

class RectangleRenderer : public Component {
public:
    RectangleRenderer(GameObject* owner);
    virtual ~RectangleRenderer();
    virtual void Render(ID2D1HwndRenderTarget* renderTarget) override;

    void SetRectangle(D2D1_RECT_F rectangle) { mRectangle = rectangle; }
    void SetColor(D2D1::ColorF color);

private:
    D2D1_RECT_F mRectangle;
    ID2D1SolidColorBrush* mBrush;
    D2D1::ColorF mColor; // 색상을 저장하는 멤버 변수 추가
};
