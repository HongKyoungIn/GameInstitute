#pragma once
#include "Component.h"

// �ʴ� ȸ�� �ӵ�

class Spinning : public Component {
public:
    Spinning(GameObject* owner, float speed);
    virtual ~Spinning() { }

    virtual void Update() override;
    virtual void Render(ID2D1HwndRenderTarget* renderTarget) override { }

private:
    float mSpeed; // ȸ�� �ӵ�
};

