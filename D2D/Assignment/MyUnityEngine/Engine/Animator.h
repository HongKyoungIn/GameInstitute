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
    void SetFlip(bool _flip) { mFlip = _flip; } // ĳ���� ������ ���� �Լ�
    void SetLoop(bool _loop) { mLoop = _loop; } // �ִϸ��̼� ������ ���� �Լ�

    D2D1_SIZE_F GetSize() { return mSize; }
    void SetSize(float width, float height); // ũ�� ���� �Լ� �߰�

private:
    AnimationAsset* currentAnimation = nullptr;
    std::wstring currentAnimationFilePath;
    float currentTime = 0.0f;
    int currentFrameIndex = 0;
    D2D1_SIZE_F mSize = { 0, 0 }; // �ִϸ��̼� ũ�� ������ ��� ���� �߰�

    bool mFlip = false; // ĳ���� ������ ���� ����
    bool mLoop = true;
};
