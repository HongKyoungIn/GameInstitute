#include "PlayerMove.h"

void PlayerMove::Update() {
    Transform* transform = mOwner->GetTransform();
    if(InputManager::GetInstance()->IsKeyHeld('A')) {
        transform->SetPosition(transform->GetPosition().x - 3.0f, transform->GetPosition().y);
    }
    if(InputManager::GetInstance()->IsKeyHeld('D')) {
        transform->SetPosition(transform->GetPosition().x + 3.0f, transform->GetPosition().y);
    }
    if(InputManager::GetInstance()->IsKeyHeld('W')) {
        transform->SetPosition(transform->GetPosition().x, transform->GetPosition().y - 3.0f);
    }
    if(InputManager::GetInstance()->IsKeyHeld('S')) {
        transform->SetPosition(transform->GetPosition().x, transform->GetPosition().y + 3.0f);
    }
    if(InputManager::GetInstance()->IsKeyPressed(VK_SPACE)) {
        // ���� ���� ����
    }
}