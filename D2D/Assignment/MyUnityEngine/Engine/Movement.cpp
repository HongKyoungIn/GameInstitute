#include "Movement.h"
#include "GameObject.h"
#include "TimeManager.h"

Movement::Movement(GameObject* owner) : Component(owner), mDirection(D2D1::Point2F(0, 0)), mSpeed(0.0f) {
    transform = mOwner->GetTransform();
}

void Movement::Update() {
    float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
    transform->SetPosition(
        transform->GetPosition().x + (mSpeed * mDirection.x * deltaTime),
        transform->GetPosition().y + (mSpeed * mDirection.y * deltaTime)
    );
}


void Movement::Render(ID2D1HwndRenderTarget* renderTarget) { }

void Movement::SetDirection(D2D1_POINT_2F dir) {
    mDirection = dir;
}

void Movement::SetSpeed(float spd) {
    mSpeed = spd;
}
