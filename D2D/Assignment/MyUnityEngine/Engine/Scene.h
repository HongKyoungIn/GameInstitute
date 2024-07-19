#pragma once
#include <vector>
#include "GameObject.h"
#include "AABB.h"
#include "Renderer.h"
#include "CommonInclude.h"

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

protected:
    std::vector<GameObject*> mGameObjects;
};

