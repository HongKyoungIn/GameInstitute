#pragma once
#include "..\Engine\Scene.h"
#include "Character.h"

class Scene3 : public Scene {
public:
    Scene3();
    virtual ~Scene3();

    bool Initialize() override;
    void HandleInput() override;
    void Update() override;

private:
    std::vector<GameObject*> enemies;
    GameObject* player = nullptr;
};
