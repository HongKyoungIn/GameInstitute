#include "Transform.h"

Transform::Transform(GameObject* owner, float x, float y) : Component(owner), x(x), y(y) { }

void Transform::Update() {
    // ����: ��ġ ���
    std::cout << "Transform Update: (" << x << ", " << y << ")" << std::endl;
}

void Transform::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
}
