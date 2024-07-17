#include "SceneManager.h"

void SceneManager::AddScene(const std::string& name, Scene* scene) {
    mScenes[name] = scene;
}

void SceneManager::SetCurrentScene(const std::string& name) {
    auto it = mScenes.find(name);
    if(it != mScenes.end()) {
        mCurrentScene = it->second;
    }
}

Scene* SceneManager::GetCurrentScene() {
    return mCurrentScene;
}

void SceneManager::Update() {
    if(mCurrentScene) {
        mCurrentScene->Update();
        mCurrentScene->HandleInput();
    }
}

void SceneManager::Render(ID2D1HwndRenderTarget* pRenderTarget) {
    if(mCurrentScene) {
        mCurrentScene->Render(pRenderTarget);
    }
}
