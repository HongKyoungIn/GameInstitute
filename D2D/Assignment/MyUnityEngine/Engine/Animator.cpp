#include "Animator.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TimeManager.h"

Animator::Animator(GameObject* owner) :
    Component(owner), currentAnimation(nullptr), currentTime(0.0f), currentFrameIndex(0) { }

Animator::~Animator() {
    if(currentAnimation) {
        std::cout << "Animator Release" << std::endl;
        Sleep(100);
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

    // 중심점을 기준으로 위치와 크기 변환을 계산
    D2D1_POINT_2F position = transform->GetPosition();

    D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(position.x, position.y);
    D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(transform->GetRotation());
    D2D1_MATRIX_3X2_F scale;

    if(mFlip) {
        scale = D2D1::Matrix3x2F::Scale(-transform->GetScale().x, transform->GetScale().y);
    }
    else {
        scale = D2D1::Matrix3x2F::Scale(transform->GetScale().x, transform->GetScale().y);
    }

    // 올바른 순서로 변환 적용
    renderTarget->SetTransform(scale * rotation * translation);

    // 이미지의 크기를 설정한 mSize를 이용해 렌더링
    D2D1_RECT_F destRect = D2D1::RectF(
        -mSize.width / 2,
        -mSize.height / 2,
        mSize.width / 2,
        mSize.height / 2
    );

    renderTarget->DrawBitmap(
        currentAnimation->GetBitmap(),
        destRect,
        1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        frame.sourceRect
    );
}

void Animator::SetSize(float width, float height) {
    mSize.width = width;
    mSize.height = height;
}