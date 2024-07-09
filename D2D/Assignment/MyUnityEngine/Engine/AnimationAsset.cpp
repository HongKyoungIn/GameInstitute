#include "AnimationAsset.h"
#include "Renderer.h"
#include "Core.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

AnimationAsset::AnimationAsset() : mBitmap(nullptr) { }

AnimationAsset::~AnimationAsset() {
    if(mBitmap) {
        mBitmap->Release();
    }
}

bool AnimationAsset::LoadSpriteImage(const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration) {
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    if(!resourceManager->CreateD2DBitmapFromFile(filePath)) {
        return false;
    }

    mBitmap = resourceManager->GetBitmap(filePath);
    D2D1_SIZE_F size = mBitmap->GetSize();
    float frameWidth = size.width / frameCountX;
    float frameHeight = size.height / frameCountY;

    mFrames.resize(frameCountX * frameCountY);
    int frameIndex = 0;
    for(int y = 0; y < frameCountY; ++y) {
        for(int x = 0; x < frameCountX; ++x) {
            mFrames[frameIndex].sourceRect = D2D1::RectF(x * frameWidth, y * frameHeight, (x + 1) * frameWidth, (y + 1) * frameHeight);
            mFrames[frameIndex].duration = frameDuration;
            mFrames[frameIndex].center = D2D1::Point2F(frameWidth / 2.0f, frameHeight / 2.0f);
            frameIndex++;
        }
    }

    return true;
}

const std::vector<FrameInfo>& AnimationAsset::GetFrames() const {
    return mFrames;
}

ID2D1Bitmap* AnimationAsset::GetBitmap() const {
    return mBitmap;
}
