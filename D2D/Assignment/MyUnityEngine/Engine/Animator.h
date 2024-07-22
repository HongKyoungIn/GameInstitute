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

    D2D1_SIZE_F GetSize() { return mSize; }
    void SetSize(float width, float height); // 크기 설정 함수 추가

private:
    AnimationAsset* currentAnimation = nullptr;
    std::wstring currentAnimationFilePath;
    float currentTime = 0.0f;
    int currentFrameIndex = 0;
    D2D1_SIZE_F mSize = { 0, 0 }; // 애니메이션 크기 저장할 멤버 변수 추가

    bool mFlip = false; // 캐릭터 반전을 위한 변수
    bool mLoop = true;
};
