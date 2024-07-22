#pragma once
#include "GameObject.h"
#include "AABB.h"
#include "Renderer.h"
#include "CommonInclude.h"
#include "Camera.h"

class Scene {
public:
    Scene();
    virtual ~Scene();

    virtual bool Initialize() = 0;
    virtual void Update();
    virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
    virtual void HandleInput() = 0;

    void AddGameObject(GameObject* gameObject);
    void RemoveGameObject(GameObject* _gameObject);
    void RemoveSpecificGameObject(const std::string& name);

    GameObject* GetCamera() const { return mMainCameraObject; }

protected:
    std::vector<GameObject*> mGameObjects;
    GameObject* mMainCameraObject; // 메인 카메라 오브젝트
    Camera* mCamera;
};

