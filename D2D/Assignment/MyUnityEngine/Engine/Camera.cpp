#include "Camera.h"
#include "Transform.h"
#include <iostream>

Camera::Camera(GameObject* owner) : Component(owner) {
    float width = 1920.0f;
    float height = 1080.0f;
    mCullingBounds.SetExtent(width / 2, height / 2);
    mCullingBounds.SetCenter(width / 2, height / 2);
}

void Camera::SetPosition(float x, float y) {
    mOwner->GetTransform()->SetPosition(x, y);
    mCullingBounds.SetCenter(x, y);
}

void Camera::SetSize(float width, float height) {
    mCullingBounds.SetExtent(width / 2, height / 2);
}

void Camera::Update() {
    // 카메라 업데이트 로직 (필요 시 구현)
}

void Camera::Render(ID2D1HwndRenderTarget* renderTarget) {
    // 카메라는 렌더링하지 않음
}

D2D1_MATRIX_3X2_F Camera::GetWorldTransform() {
    D2D1_POINT_2F pos = mOwner->GetTransform()->GetPosition();
    D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(pos.x, pos.y);

    D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(mOwner->GetTransform()->GetRotation());

    D2D1_MATRIX_3X2_F worldTransform = rotation * translation;

    Transform* parent = mOwner->GetTransform()->GetParent();
    while (parent != nullptr) {

        D2D1_POINT_2F pos = parent->GetPosition();

        worldTransform = D2D1::Matrix3x2F::Rotation(parent->GetRotation())
            * D2D1::Matrix3x2F::Translation(pos.x, pos.y);

        parent = parent->GetParent();
    }
    return worldTransform;
}
