#include "PlayerMove.h"
#include "../Engine/Movement.h"

void PlayerMove::Update() {
    
    Transform* transform = mOwner->GetTransform();
    Movement::Update();
    
    SetDirection({ 0, 0 });
    SetSpeed(0.0f);

    if(InputManager::GetInstance()->IsKeyHeld('A')) {
        transform->SetFlip(true);
        SetDirection({ -1, 0 });
        SetSpeed(1000.0f);
    }
    if(InputManager::GetInstance()->IsKeyHeld('D')) {
        transform->SetFlip(false);
        SetDirection({ 1, 0 });
        SetSpeed(1000.0f);
    }
    if(InputManager::GetInstance()->IsKeyHeld('W')) {
        SetDirection({ 0, -1 });
        SetSpeed(1000.0f);
    }
    if(InputManager::GetInstance()->IsKeyHeld('S')) {
        SetDirection({ 0, 1 });
        SetSpeed(1000.0f);
    }
    if(InputManager::GetInstance()->IsKeyPressed(VK_SPACE)) {
        // 점프 로직 구현
    }
}