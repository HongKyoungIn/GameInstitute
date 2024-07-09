#pragma once
#include "ReferenceCounter.h"
#include <d2d1.h>
#include <vector>
#include <string>

struct FrameInfo {
    D2D1_RECT_F sourceRect;
    float duration;
    D2D1_POINT_2F center;

    FrameInfo() : sourceRect{ 0, 0, 0, 0 }, duration(0.0f), center{ 0.0f, 0.0f } { }
};

class AnimationAsset : public ReferenceCounter {
public:
    AnimationAsset();
    ~AnimationAsset();

    bool LoadSpriteImage(const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration);
    const std::vector<FrameInfo>& GetFrames() const;
    ID2D1Bitmap* GetBitmap() const;

private:
    std::vector<FrameInfo> mFrames;
    ID2D1Bitmap* mBitmap;
};
