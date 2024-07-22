#pragma once

#include "Component.h"
#include <d2d1.h>

class Transform : public Component {
public:
    Transform(GameObject* owner);
    virtual ~Transform();

    void SetPosition(float _x, float _y);
    D2D1_POINT_2F GetPosition() const { return mPosition; }

    void SetScale(float x, float y);
    D2D1_POINT_2F GetScale() const { return mScale; }

    void SetRotation(float angle);
    float GetRotation() const;

    void SetParent(Transform* parent);
    Transform* GetParent() const;

    virtual void Update() override;
    virtual void Render(ID2D1HwndRenderTarget* renderTarget) override { }

    D2D1_MATRIX_3X2_F GetWorldTransform() const { return mWorldTransform; }

    void SetFlip(bool flip);

private:
    D2D1_POINT_2F mPosition;
    D2D1_POINT_2F mScale = { 1.0f, 1.0f };
    float mRotation;
    Transform* mParent;
    D2D1_MATRIX_3X2_F mWorldTransform;

    bool mFlip = false;
};