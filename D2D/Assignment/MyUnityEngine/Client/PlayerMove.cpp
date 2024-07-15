#include "PlayerMove.h"

void PlayerMove::Update() {
    Transform* transform = mOwner->GetTransform();
    if(InputManager::GetInstance()->IsKeyHeld('A')) {
        transform->SetPosition(transform->GetPosition().x - 1.0f, transform->GetPosition().y);
    }
    if(InputManager::GetInstance()->IsKeyHeld('D')) {
        transform->SetPosition(transform->GetPosition().x + 1.0f, transform->GetPosition().y);
    }
    if(InputManager::GetInstance()->IsKeyPressed(VK_SPACE)) {
        // 점프 로직 구현
    }
}