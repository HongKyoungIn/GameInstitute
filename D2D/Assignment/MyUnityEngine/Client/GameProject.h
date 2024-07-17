#pragma once
#include "../Engine/Core.h"
#include "../Engine/SceneManager.h"

class GameProject : public Core {
public:
    GameProject();
    virtual ~GameProject();

    bool Initialize(HINSTANCE hInstance, int nCmdShow) override;

protected:
    void Update() override;
    void FixedUpdate() override;
    void Render() override;

private:
    void HandleInput();
    bool mSpacePressed;
    bool mDelPressed;
};

