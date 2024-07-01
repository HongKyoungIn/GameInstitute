#pragma once

class GameObject;
#include <d2d1.h>

class Component {
public:
    Component() : mOwner(nullptr) { }
    Component(GameObject* owner) : mOwner(owner) { }
    virtual ~Component() { }

    virtual void Update() = 0;
    virtual void Render(ID2D1HwndRenderTarget* renderTarget) = 0;

protected:
    GameObject* mOwner;
};
