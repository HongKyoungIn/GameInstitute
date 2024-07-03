#include "Game1.h"
#include "../Engine/SpriteRenderer.h"
#include "../Engine/Transform.h"

bool Game1::Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow) {
    if(!Core::Initialize(hInstance, nCmdShow)) {
        return FALSE;
    }

    // 부모 오브젝트 생성
    {
        mPlayer1 = new GameObject("Player1");
        Transform* transform = mPlayer1->GetTransform();
        transform->SetPosition(300.0f, 300.0f);
        transform->SetRotation(180.0f);
        SpriteRenderer* spriteRenderer = mPlayer1->AddComponent<SpriteRenderer>();
        spriteRenderer->LoadBitmapFromFile(L"../Resource/Sun.png");
        spriteRenderer->SetSize(300.0f, 300.0f);

        AddGameObject(mPlayer1);
    }

    {
        mPlayer2 = new GameObject("Player2");
        Transform* transform = mPlayer2->GetTransform();
        transform->SetPosition(600.0f, 600.0f);
        SpriteRenderer* spriteRenderer = mPlayer2->AddComponent<SpriteRenderer>();
        spriteRenderer->LoadBitmapFromFile(L"../Resource/Moon.png");
        spriteRenderer->SetSize(200.0f, 200.0f);

        AddGameObject(mPlayer2);
    }

    // 자식 오브젝트 생성
    {
        GameObject* mPlayer3 = new GameObject("Player3");
        Transform* transform = mPlayer3->GetTransform();
        transform->SetPosition(0, 0);  // 부모 오브젝트로부터 상대적인 위치

        SpriteRenderer* spriteRenderer = mPlayer3->AddComponent<SpriteRenderer>();
        spriteRenderer->LoadBitmapFromFile(L"../Resource/Moon.png");
        spriteRenderer->SetSize(200.0f, 200.0f);

        mPlayer1->AddChild(mPlayer3);  // Player1을 부모로 설정

        AddGameObject(mPlayer3);
    }

    return true;
}

void Game1::Update() {
    Core::Update();
}

void Game1::Render() {
    Core::Render();
}
