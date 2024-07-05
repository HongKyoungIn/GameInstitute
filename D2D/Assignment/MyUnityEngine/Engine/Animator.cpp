#include "Animator.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TimeManager.h"

Animator::Animator(GameObject* owner) : Component(owner), currentAnimation(nullptr), currentTime(0.0f), currentFrameIndex(0) { }

Animator::~Animator() {
    if(currentAnimation) {
        ResourceManager::GetInstance()->ReleaseAnimation(currentAnimationFilePath);
    }
}

void Animator::SetAnimation(const std::wstring& filePath, int frameCount, float frameDuration) {
    if(currentAnimation) {
        ResourceManager::GetInstance()->ReleaseAnimation(currentAnimationFilePath);
    }
    currentAnimation = ResourceManager::GetInstance()->LoadAnimation(filePath, frameCount, frameDuration);
    currentAnimationFilePath = filePath;
    currentTime = 0.0f;
    currentFrameIndex = 0;
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
    Transform* transform = mOwner->GetTransform();  // 오브젝트의 변환 정보를 가져옴

    D2D1_POINT_2F position = transform->GetPosition();  // 오브젝트의 위치를 가져옴
    D2D1_RECT_F destinationRect = D2D1::RectF(
        position.x,
        position.y,
        position.x + (frame.sourceRect.right - frame.sourceRect.left),
        position.y + (frame.sourceRect.bottom - frame.sourceRect.top)
    );

    renderTarget->DrawBitmap(
        currentAnimation->GetBitmap(),
        destinationRect,
        1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        frame.sourceRect
    );
}
