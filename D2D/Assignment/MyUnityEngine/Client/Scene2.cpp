#include "Scene2.h"
#include "../Engine/Animator.h"
#include "../Engine/VideoMemoryDisplay.h"
#include "PlayerMove.h"
#include "../Engine/SceneManager.h"

Scene2::Scene2() { }

Scene2::~Scene2() { }

bool Scene2::Initialize() {
    // Add game objects and components here

    // VRAM usage display
    GameObject* VRAM = new GameObject("VRAM");
    Transform* transform = VRAM->GetTransform();
    transform->SetPosition(60, 10);
    transform->SetScale(2, 2);
    VRAM->SetLayer(2);  // UI layer

    VideoMemoryDisplay* videoMemoryDisplay = VRAM->AddComponent<VideoMemoryDisplay>();
    AddGameObject(VRAM);

    // Reversed Run animation
    GameObject* player1 = new GameObject("Player1");
    transform = player1->GetTransform();
    transform->SetPosition(400, 400);
    Animator* animator = player1->AddComponent<Animator>();
    animator->SetFlip(true);
    animator->SetAnimation(L"../Resource/Run.png", 10, 1, 0.1f);
    animator->SetSize(100, 100);
    AddGameObject(player1);

    // Normal Run animation
    GameObject* player2 = new GameObject("Player2");
    transform = player2->GetTransform();
    transform->SetPosition(500, 500);
    player2->SetLayer(1);  // Player layer
    PlayerMove* playerMove = player2->AddComponent<PlayerMove>();
    animator = player2->AddComponent<Animator>();
    animator->SetAnimation(L"../Resource/Run.png", 10, 1, 0.1f);
    animator->SetSize(100, 100);
    AddGameObject(player2);

    // Background
    GameObject* background = new GameObject("BackGround");
    transform = background->GetTransform();
    transform->SetPosition(1920 / 2, 1080 / 2);
    background->SetLayer(0);  // Background layer
    animator = background->AddComponent<Animator>();
    animator->SetFlip(true);
    animator->SetAnimation(L"../Resource/midnight.png", 2, 2, 1.0f);
    animator->SetSize(1920, 1080);
    AddGameObject(background);

    return true;
}

void Scene2::HandleInput() {
    if((GetAsyncKeyState(VK_SPACE) & 0x8000) && !mSpacePressed) {
        mSpacePressed = true;
        D2D1_POINT_2F position = D2D1::Point2F((float)(rand() % 1920), (float)(rand() % 1080));
        CreateCharacter(position, L"../Resource/Run.png", 8, 1, 0.1f);
    }
    else if(!(GetAsyncKeyState(VK_SPACE) & 0x8000)) {
        mSpacePressed = false;
    }

    if((GetAsyncKeyState(VK_DELETE) & 0x8000) && !mDelPressed) {
        mDelPressed = true;
        // Example of removing a specific game object in the current scene
        Scene* currentScene = SceneManager::GetInstance()->GetCurrentScene();
        if(currentScene) {
            currentScene->RemoveSpecificGameObject("Character");
        }
    }
    else if(!(GetAsyncKeyState(VK_DELETE) & 0x8000)) {
        mDelPressed = false;
    }

    if((GetAsyncKeyState(VK_F1) & 0x8000)) {
        SceneManager::GetInstance()->SetCurrentScene("Scene1");
    }

    if((GetAsyncKeyState(VK_F2) & 0x8000)) {
        SceneManager::GetInstance()->SetCurrentScene("Scene2");
    }
}

void Scene2::CreateCharacter(D2D1_POINT_2F position, const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration) {
    GameObject* character = new GameObject("Character");
    Transform* transform = character->GetTransform();
    transform->SetPosition(position.x, position.y);

    Animator* animator = character->AddComponent<Animator>();
    animator->SetSize(100, 100);
    animator->SetAnimation(filePath, frameCountX, frameCountY, frameDuration);

    AddGameObject(character);
}