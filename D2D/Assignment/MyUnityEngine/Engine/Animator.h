#pragma once
#include "Component.h"
#include "AnimationAsset.h"

class Animator : public Component {
public:
    Animator(GameObject* owner);
    virtual ~Animator();

    void SetAnimation(const std::wstring& filePath, int frameCount, float frameDuration);
    void Update() override;
    void Render(ID2D1HwndRenderTarget* renderTarget) override;

private:
    AnimationAsset* currentAnimation = nullptr;
    std::wstring currentAnimationFilePath;
    float currentTime = 0.0f;
    int currentFrameIndex = 0;
};
