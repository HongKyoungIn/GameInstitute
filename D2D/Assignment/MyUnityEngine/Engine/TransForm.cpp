#include "Transform.h"

Transform::Transform(GameObject* owner)
    : Component(owner), mRotation(0.0f), mParent(nullptr) {
    mPosition.x = 0.0f;
    mPosition.y = 0.0f;
    mWorldTransform = D2D1::Matrix3x2F::Identity();
}

Transform::~Transform() { }

void Transform::SetPosition(float _x, float _y) {
    mPosition.x = _x;
    mPosition.y = _y;
}

void Transform::SetScale(float x, float y) {
    mScale.x = x;
    mScale.y = y;
}

void Transform::SetRotation(float angle) {
    mRotation = angle;
}

float Transform::GetRotation() const {
    return mRotation;
}

void Transform::SetParent(Transform* parent) {
    mParent = parent;
}

Transform* Transform::GetParent() const {
    return mParent;
}

void Transform::Update() {
    D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(mPosition.x, mPosition.y);
    D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(mRotation);
    D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(mScale.x, mScale.y);

    D2D1_MATRIX_3X2_F localTransform = scale * rotation * translation;

    if(mParent) {
        mWorldTransform = localTransform * mParent->GetWorldTransform();
    }
    else {
        mWorldTransform = localTransform;
    }
}
