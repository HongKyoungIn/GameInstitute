#pragma once
#include "Component.h"
#include "Renderer.h"

class VideoMemoryDisplay : public Component {
public:
    VideoMemoryDisplay(GameObject* owner);
    ~VideoMemoryDisplay();

    void Update() override;
    void Render(ID2D1HwndRenderTarget* renderTarget) override;

private:
    SIZE_T GetUsedVRAM();
    SIZE_T GetTotalVRAM();

    IDWriteTextFormat* mTextFormat;
    ID2D1SolidColorBrush* mBrush;
    std::wstring mText;
};
