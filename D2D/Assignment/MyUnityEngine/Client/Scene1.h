#pragma once
#include "../Engine/Scene.h"

class Scene1 : public Scene {
public:
    Scene1();
    virtual ~Scene1();

    bool Initialize() override;
    void HandleInput() override;

    void CreateCharacter(D2D1_POINT_2F position, const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration);

private:
    bool mSpacePressed;
    bool mDelPressed;
};