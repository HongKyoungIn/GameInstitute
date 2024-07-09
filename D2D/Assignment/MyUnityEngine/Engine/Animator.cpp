#include "Animator.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TimeManager.h"

Animator::Animator(GameObject* owner) :
    Component(owner), currentAnimation(nullptr), currentTime(0.0f), currentFrameIndex(0) { }

Animator::~Animator() {
    if(currentAnimation) {
        ResourceManager::GetInstance()->ReleaseAnimation(currentAnimationFilePath);
    }
}

void Animator::SetAnimation(const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration) {
    if(currentAnimation) {
        ResourceManager::GetInstance()->ReleaseAnimation(currentAnimationFilePath);
    }

    currentAnimation = ResourceManager::GetInstance()->LoadAnimationImage(filePath, frameCountX, frameCountY, frameDuration);
    if(currentAnimation) {
        currentFrameIndex = 0;
        currentTime = 0.0f;
    }
}

void Animator::Update() {
    if(!currentAnimation) return;

    currentTime += TimeManager::GetInstance()->GetDeltaTime();
    const std::vector<FrameInfo>& frames = currentAnimation->GetFrames();

    while(currentTime > frames[currentFrameIndex].duration) {
        currentTime -= frames[currentFrameIndex].duration;
        currentFrameIndex = (currentFrameIndex + 1) % frames.size();
    }
}

void Animator::Render(ID2D1HwndRenderTarget* renderTarget) {
    if(!currentAnimation) return;

    const FrameInfo& frame = currentAnimation->GetFrames()[currentFrameIndex];
    Transform* transform = mOwner->GetTransform();

    D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(transform->GetPosition().x - frame.center.x, transform->GetPosition().y - frame.center.y);
    D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(transform->GetRotation(), transform->GetPosition());
    D2D1_MATRIX_3X2_F scale;

    if(mFlip) {
        scale = D2D1::Matrix3x2F::Scale(-transform->GetScale().x, transform->GetScale().y, transform->GetPosition());
    }
    else {
        scale = D2D1::Matrix3x2F::Scale(transform->GetScale().x, transform->GetScale().y, transform->GetPosition());
    }

    renderTarget->SetTransform(scale * rotation * translation);
    renderTarget->DrawBitmap(currentAnimation->GetBitmap(), D2D1::RectF(0.0f, 0.0f, frame.sourceRect.right - frame.sourceRect.left, frame.sourceRect.bottom - frame.sourceRect.top), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame.sourceRect);
}
