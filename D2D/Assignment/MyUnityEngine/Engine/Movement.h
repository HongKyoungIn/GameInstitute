#pragma once
#include "Component.h"
#include <d2d1.h>

class Transform;

class Movement : public Component {
public:
    Movement(GameObject* owner);

    void Update() override;
    void Render(ID2D1HwndRenderTarget* renderTarget) override;

    void SetDirection(D2D1_POINT_2F direction);
    void SetSpeed(float speed);

private:
    Transform* transform;
    D2D1_POINT_2F mDirection;
    float mSpeed;
};
