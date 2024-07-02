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
        Transform* transform1 = mPlayer1->GetTransform();
        transform1->SetPosition(300.0f, 300.0f);

        SpriteRenderer* spriteRenderer1 = mPlayer1->AddComponent<SpriteRenderer>();
        spriteRenderer1->LoadBitmapFromFile(L"../Resource/Sun.png");
        spriteRenderer1->SetSize(100.0f, 100.0f);

        AddGameObject(mPlayer1);
    }

    // 자식 오브젝트 생성
    {
        GameObject* mPlayer2 = new GameObject("Player2");
        Transform* transform2 = mPlayer2->GetTransform();
        transform2->SetPosition(0, 0);  // 부모 오브젝트로부터 상대적인 위치

        SpriteRenderer* spriteRenderer2 = mPlayer2->AddComponent<SpriteRenderer>();
        spriteRenderer2->LoadBitmapFromFile(L"../Resource/Moon.png");
        spriteRenderer2->SetSize(50.0f, 50.0f);

        mPlayer1->AddChild(mPlayer2);  // Player1을 부모로 설정

        AddGameObject(mPlayer2);
    }

    return true;
}

void Game1::Update() {
    Core::Update();
}

void Game1::Render() {
    Core::Render();
}
