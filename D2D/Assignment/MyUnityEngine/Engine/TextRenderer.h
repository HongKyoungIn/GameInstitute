#pragma once
#include "Component.h"
#include <string>
#include <d2d1.h>
#include <dwrite.h>

class TextRenderer : public Component {
public:
    TextRenderer(GameObject* owner);
    virtual ~TextRenderer();

    void Update() override;
    void Render(ID2D1HwndRenderTarget* renderTarget) override;

    void SetText(const std::wstring& text);
    void SetColor(const D2D1_COLOR_F& color);
    void SetFontSize(float size);

private:
    std::wstring mText;
    D2D1_COLOR_F mColor;
    float mFontSize;
    IDWriteTextFormat* mTextFormat;
    ID2D1SolidColorBrush* mBrush;
};

