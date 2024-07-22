#include "GameProject.h"
#include "Scene1.h" // Include your specific Scene header files here
#include "Scene2.h" // Example of another scene
// #include "Scene3.h" // Example of another scene

GameProject::GameProject() : mSpacePressed(false), mDelPressed(false) { }

GameProject::~GameProject() { }

bool GameProject::Initialize(HINSTANCE hInstance, int nCmdShow) {
    if(!Core::Initialize(hInstance, nCmdShow)) {
        return false;
    }

    // Initialize and add scenes
    Scene1* scene1 = new Scene1();
    scene1->Initialize();
    SceneManager::GetInstance()->AddScene("Scene1", scene1);

    Scene2* scene2 = new Scene2(); // Another example scene
    scene2->Initialize();
    SceneManager::GetInstance()->AddScene("Scene2", scene2);

    //Scene3* scene3 = new Scene3(); // Another example scene
    //scene3->Initialize();
    //SceneManager::GetInstance()->AddScene("Scene3", scene3);

    // Set initial scene
    SceneManager::GetInstance()->SetCurrentScene("Scene1");

    return true;
}

void GameProject::Update() {
    Core::Update();
}

void GameProject::FixedUpdate() {
    Core::FixedUpdate();
}

void GameProject::Render() {
    Core::Render();
}