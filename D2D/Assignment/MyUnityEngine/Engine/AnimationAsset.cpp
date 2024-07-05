#include "AnimationAsset.h"
#include "Renderer.h"
#include "Core.h"
#include "ResourceManager.h"

AnimationAsset::AnimationAsset() : m_Bitmap(nullptr) { }

AnimationAsset::~AnimationAsset() {
    if(m_Bitmap) {
        m_Bitmap->Release();
    }
}

bool AnimationAsset::Load(const std::wstring& filePath, int frameCount, float frameDuration) {
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    if(!resourceManager->CreateD2DBitmapFromFile(filePath)) {
        return false;
    }

    m_Bitmap = resourceManager->GetBitmap(filePath);
    D2D1_SIZE_F size = m_Bitmap->GetSize();
    float frameWidth = size.width / frameCount;
    float frameHeight = size.height;

    m_Frames.resize(frameCount);
    for(int i = 0; i < frameCount; ++i) {
        m_Frames[i].sourceRect = D2D1::RectF(i * frameWidth, 0, (i + 1) * frameWidth, frameHeight);
        m_Frames[i].duration = frameDuration;
    }

    return true;
}

const std::vector<FrameInfo>& AnimationAsset::GetFrames() const {
    return m_Frames;
}

ID2D1Bitmap* AnimationAsset::GetBitmap() const {
    return m_Bitmap;
}
