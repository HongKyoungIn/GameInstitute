#include "Transform.h"

Transform::Transform(GameObject* owner)
    : Component(owner), mParent(nullptr) {
    mPosition[0] = 0.0f;
    mPosition[1] = 0.0f;
    mWorldTransform = D2D1::Matrix3x2F::Identity();
}

Transform::~Transform() { }

void Transform::SetPosition(float x, float y) {
    mPosition[0] = x;
    mPosition[1] = y;
}

void Transform::GetPosition(float& x, float& y) const {
    x = mPosition[0];
    y = mPosition[1];
}

void Transform::SetParent(Transform* parent) {
    mParent = parent;
}

Transform* Transform::GetParent() const {
    return mParent;
}

void Transform::Update() {
    D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(mPosition[0], mPosition[1]);
    if(mParent) {
        mWorldTransform = translation * mParent->GetWorldTransform();
    }
    else {
        mWorldTransform = translation;
    }
}
