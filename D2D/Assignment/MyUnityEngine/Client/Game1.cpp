#include "Game1.h"
#include "../Engine/SpriteRenderer.h"
#include "../Engine/Transform.h"
#include "../Engine/Spinning.h"

bool Game1::Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow) {
    if(!Core::Initialize(hInstance, nCmdShow)) {
        return FALSE;
    }

    // �θ� ������Ʈ ����
    {
        mPlayer1 = new GameObject("Player1");
        Transform* transform = mPlayer1->GetTransform();
        transform->SetPosition(1920.0f / 2, 1080.0f / 2);
        transform->SetRotation(180.0f);

        SpriteRenderer* spriteRenderer = mPlayer1->AddComponent<SpriteRenderer>();
        Spinning* spinning = mPlayer1->AddComponent<Spinning>(45.0f);

        spriteRenderer->LoadBitmapFromFile(L"../Resource/Sun.png");
        spriteRenderer->SetSize(300.0f, 300.0f);

        AddGameObject(mPlayer1);
    }

    {
        mPlayer2 = new GameObject("Player2");
        Transform* transform = mPlayer2->GetTransform();
        transform->SetPosition(500.0f, 0.0f);
        Spinning* spinning = mPlayer2->AddComponent<Spinning>(90.0f);

        SpriteRenderer* spriteRenderer = mPlayer2->AddComponent<SpriteRenderer>();
        spriteRenderer->LoadBitmapFromFile(L"../Resource/Earth.png");
        spriteRenderer->SetSize(200.0f, 200.0f);

        mPlayer2->SetParent(mPlayer1);  // Player1�� �θ�� ����

        AddGameObject(mPlayer2);
    }

    // �ڽ� ������Ʈ ����
    {
        GameObject* mPlayer3 = new GameObject("Player3");
        Transform* transform = mPlayer3->GetTransform();
        transform->SetPosition(150, 0);  // �θ� ������Ʈ�κ��� ������� ��ġ
        Spinning* spinning = mPlayer3->AddComponent<Spinning>(180.0f);

        SpriteRenderer* spriteRenderer = mPlayer3->AddComponent<SpriteRenderer>();
        spriteRenderer->LoadBitmapFromFile(L"../Resource/Moon.png");
        spriteRenderer->SetSize(100.0f, 100.0f);

        mPlayer3->SetParent(mPlayer2);  // Player1�� �θ�� ����

        AddGameObject(mPlayer3);
    }
    // �ڽ� ������Ʈ ���� �׽�Ʈ
    // RemoveGameObject(mPlayer1);

    return true;
}

void Game1::Update() {
    Core::Update();
    HandleInput();  // Ű �Է� ó�� �Լ� ȣ��
}

void Game1::FixedUpdate() { 
    Core::FixedUpdate();
}

void Game1::Render() {
    Core::Render();
}

void Game1::HandleInput() {
    if(GetAsyncKeyState(VK_SPACE) & 0x8000) {
         if(mPlayer1) {
            RemoveGameObject(mPlayer1);
            mPlayer1 = nullptr;  // ������Ʈ�� ������ �� �����͸� nullptr�� ����
        }
    }
}