#pragma once

class GameObject;
#include <d2d1.h>
#include <iostream>

class Component {
public:
    Component() : mOwner(nullptr) { }
    Component(GameObject* owner) : mOwner(owner) { }
    virtual ~Component() {
        std::cout << "Component Release" << std::endl;
        Sleep(100);
    }

    virtual void Update() = 0;
    virtual void Render(ID2D1HwndRenderTarget* renderTarget) = 0;

protected:
    GameObject* mOwner;
};
