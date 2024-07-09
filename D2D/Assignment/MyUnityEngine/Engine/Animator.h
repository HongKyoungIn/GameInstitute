#pragma once
#include "Component.h"
#include "AnimationAsset.h"

class Animator : public Component {
public:
    Animator(GameObject* owner);
    virtual ~Animator();

    void SetAnimation(const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration);
    void Update() override;
    void Render(ID2D1HwndRenderTarget* renderTarget) override;
    void SetFlip(bool _flip) { mFlip = _flip; } // 캐릭터 반전을 위한 함수
    void SetLoop(bool _loop) { mLoop = _loop; } // 애니메이션 루프를 위한 함수

private:
    AnimationAsset* currentAnimation = nullptr;
    std::wstring currentAnimationFilePath;
    float currentTime = 0.0f;
    int currentFrameIndex = 0;

    bool mFlip = false; // 캐릭터 반전을 위한 변수
    bool mLoop = true;
};
