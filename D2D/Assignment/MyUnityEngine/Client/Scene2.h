#pragma once
#include "D:\GameInstitute\D2D\Assignment\MyUnityEngine\Engine\Scene.h"

class Scene2 : public Scene {
public:
    Scene2();
    virtual ~Scene2();

    bool Initialize() override;
    void HandleInput() override;

    void CreateCharacter(D2D1_POINT_2F position, const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration);

private:
    bool mSpacePressed;
    bool mDelPressed;
};