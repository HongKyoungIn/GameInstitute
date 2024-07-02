#pragma once

#include "Renderer.h"
#include <string>

class SpriteRenderer : public Renderer {
public:
    SpriteRenderer(GameObject* owner);
    virtual ~SpriteRenderer();

    bool LoadBitmapFromFile(const std::wstring& filePath);
    void SetSize(float width, float height);

    virtual void Render(ID2D1HwndRenderTarget* renderTarget) override;

private:
    ID2D1Bitmap* mBitmap;
    D2D1_RECT_F mDestRect;
    float mWidth = 0.0f;
    float mHeight = 0.0f;
};