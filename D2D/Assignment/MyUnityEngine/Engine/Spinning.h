#pragma once
#include "Component.h"

// 초당 회전 속도

class Spinning : public Component {
public:
    Spinning(GameObject* owner, float speed);
    virtual ~Spinning() { }

    virtual void Update() override;
    virtual void Render(ID2D1HwndRenderTarget* renderTarget) override { }

private:
    float mSpeed; // 회전 속도
};

