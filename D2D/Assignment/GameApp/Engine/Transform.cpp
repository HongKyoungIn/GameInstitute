#include "Transform.h"

Transform::Transform(GameObject* owner, float x, float y) : Component(owner), x(x), y(y) { }

void Transform::Update() {
    // 예제: 위치 출력
    std::cout << "Transform Update: (" << x << ", " << y << ")" << std::endl;
}

void Transform::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
}
