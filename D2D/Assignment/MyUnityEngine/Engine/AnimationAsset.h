#pragma once
#include "ReferenceCounter.h"
#include <d2d1.h>
#include <vector>
#include <string>

struct FrameInfo {
    D2D1_RECT_F sourceRect;
    float duration;
};

class AnimationAsset : public ReferenceCounter {
public:
    AnimationAsset();
    ~AnimationAsset();

    bool Load(const std::wstring& filePath, int frameCount, float frameDuration);
    const std::vector<FrameInfo>& GetFrames() const;
    ID2D1Bitmap* GetBitmap() const;

private:
    std::vector<FrameInfo> m_Frames;
    ID2D1Bitmap* m_Bitmap;
};
