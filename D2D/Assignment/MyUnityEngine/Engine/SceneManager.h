#pragma once
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager {
public:
    static SceneManager* GetInstance() {
        static SceneManager instance;
        return &instance;
    }

    void AddScene(const std::string& name, Scene* scene);
    void SetCurrentScene(const std::string& name);
    Scene* GetCurrentScene();

    void Update();
    void Render(ID2D1HwndRenderTarget* pRenderTarget);

private:
    SceneManager() = default;
    ~SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    std::unordered_map<std::string, Scene*> mScenes;
    Scene* mCurrentScene = nullptr;
};
