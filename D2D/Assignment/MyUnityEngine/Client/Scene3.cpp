#include "Scene3.h"
#include "../Engine/CircleRenderer.h"
#include "../Engine/InputManager.h"
#include "../Engine/TimeManager.h"
#include "../Engine/SceneManager.h"
#include "PlayerMove.h"
#include "../Engine/Animator.h"

Scene3::Scene3() { }

Scene3::~Scene3() { }

bool Scene3::Initialize() {
    {
        // Background
        GameObject* background = new GameObject("BackGround");
        Transform* transform = background->GetTransform();
        transform->SetPosition(1920 / 2, 1080 / 2);
        background->SetLayer(0);  // Background layer
        Animator* animator = background->AddComponent<Animator>();
        animator->SetFlip(true);
        animator->SetAnimation(L"../Resource/midnight.png", 2, 2, 1.0f);
        animator->SetSize(1920, 1080);
        AddGameObject(background);
    }

    // 플레이어 캐릭터 생성 및 초기화
    player = new GameObject("player");
    player->AddComponent<Character>(Character::TYPE_HUMAN, nullptr, 0);
    Transform* playerTransform = player->GetTransform();
    playerTransform->SetPosition(400, 400);
    player->AddComponent<CircleRenderer>();

    // PlayerMove 설정
    player->AddComponent<PlayerMove>();

    // CircleRenderer 설정
    CircleRenderer* playerCircle = player->GetComponent<CircleRenderer>();
    playerCircle->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
    playerCircle->SetRadius(20.0f);
    playerCircle->SetCenter(D2D1::Point2F(0, 0));

    player->AddChild(mMainCameraObject);
    AddGameObject(player);

    // 적 캐릭터 생성 및 초기화
    for (int i = 0; i < 5; ++i) {
        DWORD enemyStateTransitions[][3] = {
            { Character::STATE_STAND, Character::EVENT_FINDTARGET, Character::STATE_FOLLOW },
            { Character::STATE_STAND, Character::EVENT_BEATTACKED, Character::STATE_ATTACK },
            { Character::STATE_STAND, Character::EVENT_DUBIOUS, Character::STATE_MOVE },
            { Character::STATE_MOVE, Character::EVENT_FINDTARGET, Character::STATE_FOLLOW },
            { Character::STATE_MOVE, Character::EVENT_STOPWALK, Character::STATE_STAND },
            { Character::STATE_ATTACK, Character::EVENT_LOSTTARGET, Character::STATE_STAND },
            { Character::STATE_ATTACK, Character::EVENT_HEALTHDRAINED, Character::STATE_RUNAWAY },
            { Character::STATE_ATTACK, Character::EVENT_OUTOFATTACK, Character::STATE_FOLLOW },
            { Character::STATE_FOLLOW, Character::EVENT_WITHINATTACK, Character::STATE_ATTACK },
            { Character::STATE_FOLLOW, Character::EVENT_LOSTTARGET, Character::STATE_STAND },
            { Character::STATE_RUNAWAY, Character::EVENT_LOSTTARGET, Character::STATE_STAND },
        };

        GameObject* enemyObject = new GameObject("enemy");
        Character* enemyCharacter = enemyObject->AddComponent<Character>(Character::TYPE_AI, enemyStateTransitions, 11);
        Transform* enemyTransform = enemyObject->GetTransform();
        enemyTransform->SetPosition(rand() % 640, rand() % 480);

        // CircleRenderer 설정
        CircleRenderer* enemyCircle = enemyObject->AddComponent<CircleRenderer>();
        enemyCircle->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
        enemyCircle->SetRadius(15.0f);
        enemyCircle->SetCenter(D2D1::Point2F(0, 0));
        
        enemies.push_back(enemyObject);
        AddGameObject(enemyObject);
    }

    

    return true;
}

void Scene3::HandleInput() {
    if ((GetAsyncKeyState(VK_F1) & 0x8000)) {
        SceneManager::GetInstance()->SetCurrentScene("Scene1");
    }

    if ((GetAsyncKeyState(VK_F2) & 0x8000)) {
        SceneManager::GetInstance()->SetCurrentScene("Scene2");
    }

    if ((GetAsyncKeyState(VK_F3) & 0x8000)) {
        SceneManager::GetInstance()->SetCurrentScene("Scene3");
    }
}

void Scene3::Update() {
    Scene::Update();

    float timeDelta = TimeManager::GetInstance()->GetDeltaTime();

    // 플레이어 업데이트
    if (player) {
        Character* playerCharacter = player->GetComponent<Character>();
        playerCharacter->Update();
    }

    // 적 캐릭터 업데이트
    for (GameObject* enemy : enemies) {
        Character* enemyCharacter = enemy->GetComponent<Character>();
        enemyCharacter->Update(player, timeDelta);
    }
}
