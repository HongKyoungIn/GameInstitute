#include "Spinning.h"
#include "Transform.h"
#include "GameObject.h"
#include "TimeManager.h"

Spinning::Spinning(GameObject* owner, float speed)
    : Component(owner), mSpeed(speed) { }

void Spinning::Update() {
    Transform* transform = mOwner->GetComponent<Transform>();

    if(transform) {
        float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
        transform->SetRotation(transform->GetRotation() + mSpeed * deltaTime);
    }
}