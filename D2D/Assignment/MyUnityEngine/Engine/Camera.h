#pragma once

#include "Component.h"
#include "AABB.h"
#include <vector>
#include <d2d1.h>
#include "GameObject.h"

class Camera : public Component {
public:
    Camera(GameObject* owner);

    void SetPosition(float x, float y);
    void SetSize(float width, float height);
    void Update() override;
    void Render(ID2D1HwndRenderTarget* renderTarget) override;

    D2D1_MATRIX_3X2_F GetWorldTransform();

    AABB GetCullingBounds() const { return mCullingBounds; }

private:
    AABB mCullingBounds;
};
