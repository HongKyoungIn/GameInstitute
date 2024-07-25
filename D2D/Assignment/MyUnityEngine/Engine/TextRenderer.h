#pragma once
#include "..\Engine\Component.h"
#include <d2d1.h>
#include <dwrite.h>
#include <string>

class TextRenderer : public Component {
public:
    TextRenderer(GameObject* owner);
    ~TextRenderer();

    void Update() override;
    void Render(ID2D1HwndRenderTarget* renderTarget) override;

    void SetText(const std::wstring& text);
    void SetFontSize(float size);
    void SetFontColor(D2D1_COLOR_F color);
    void SetPosition(D2D1_POINT_2F position);

private:
    void UpdateTextFormat();

    std::wstring mText;
    float mFontSize;
    D2D1_COLOR_F mFontColor;
    D2D1_POINT_2F mPosition; // 텍스트 위치를 지정할 수 있도록 추가
    IDWriteTextFormat* mTextFormat;
    ID2D1SolidColorBrush* mBrush;
};
