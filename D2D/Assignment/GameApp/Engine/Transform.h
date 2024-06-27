#pragma once

#include "Component.h"
#include <iostream>

class Transform : public Component {
public:
    Transform(GameObject* owner, float x = 0, float y = 0);

    void Update() override;

    void SetPosition(float newX, float newY);

private:
    float x, y;
};
