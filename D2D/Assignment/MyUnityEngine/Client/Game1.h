#pragma once

#include "resource.h"
#include "../Engine/Core.h"

class Game1 : public Core {
public:
    virtual bool Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow) override;
    void Update() override;
    void Render() override;
    void HandleInput();

private:
    GameObject* mPlayer1;
    GameObject* mPlayer2;
};
