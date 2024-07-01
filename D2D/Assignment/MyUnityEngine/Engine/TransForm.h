#pragma once

#include "Component.h"
#include <d2d1.h>

class Transform : public Component {
public:
    Transform(GameObject* owner);
    virtual ~Transform();

    void SetPosition(float x, float y);
    void GetPosition(float& x, float& y) const;

    void SetParent(Transform* parent);
    Transform* GetParent() const;

    virtual void Update() override;
    virtual void Render(ID2D1HwndRenderTarget* renderTarget) override { }

    D2D1_MATRIX_3X2_F GetWorldTransform() const { return mWorldTransform; }

private:
    float mPosition[2];
    Transform* mParent;
    D2D1_MATRIX_3X2_F mWorldTransform;
};