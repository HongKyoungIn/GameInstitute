#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <unordered_map>
#include <string>
#include "Renderer.h"
#include "AnimationAsset.h"

class ResourceManager {
public:
    static ResourceManager* GetInstance() {
        static ResourceManager instance;
        return &instance;
    }

    bool CreateD2DBitmapFromFile(const std::wstring& filePath);
    void ReleaseD2DBitmap(const std::wstring& strFilePath);
    ID2D1Bitmap* GetBitmap(const std::wstring& filePath);

    void ReleaseAllResources();

    AnimationAsset* LoadAnimationImage(const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration);
    void ReleaseAnimation(const std::wstring& filePath);

private:
    ResourceManager();
    ~ResourceManager();

    void SafeRelease(IUnknown* resource);

    std::unordered_map<std::wstring, ID2D1Bitmap*> mBitmapMap;
    std::unordered_map<std::wstring, AnimationAsset*> mAnimations;
};