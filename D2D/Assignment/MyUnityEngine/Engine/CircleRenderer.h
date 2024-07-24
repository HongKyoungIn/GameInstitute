#pragma once

#include <d2d1.h>
#include "Component.h"

class CircleRenderer : public Component {
public:
    CircleRenderer(GameObject* owner);
    virtual ~CircleRenderer();

    void SetColor(D2D1::ColorF color);
    void SetRadius(float radius);
    void SetCenter(D2D1_POINT_2F center);

    virtual void Update() override { };
    virtual void Render(ID2D1HwndRenderTarget* renderTarget) override;

private:
    ID2D1SolidColorBrush* mBrush;
    D2D1::ColorF mColor;
    float mRadius;
    D2D1_POINT_2F mCenter;
};