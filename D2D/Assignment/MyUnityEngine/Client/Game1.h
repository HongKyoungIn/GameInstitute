#pragma once

#include "resource.h"
#include "../Engine/Core.h"

class Game1 : public Core {
public:
    virtual bool Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow) override;
    void Update() override;
    virtual void FixedUpdate() override;
    void Render() override;
    void CreateCharacter(D2D1_POINT_2F position, const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration);
    void HandleInput();

private:
    GameObject* mPlayer1;
    GameObject* mPlayer2;
    bool mSpacePressed;
    bool mDelPressed;
};
