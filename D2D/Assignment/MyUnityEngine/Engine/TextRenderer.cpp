#include "TextRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Core.h"

TextRenderer::TextRenderer(GameObject* owner)
    : Component(owner), mText(L""), mColor(D2D1::ColorF(D2D1::ColorF::White)), mFontSize(20.0f), mTextFormat(nullptr), mBrush(nullptr) {
    Renderer* renderer = Core::GetRenderer();
    renderer->GetDWriteFactory()->CreateTextFormat(
        L"Arial",
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        mFontSize,
        L"",
        &mTextFormat
    );
    renderer->GetRenderTarget()->CreateSolidColorBrush(mColor, &mBrush);
}

TextRenderer::~TextRenderer() {
    if(mTextFormat) mTextFormat->Release();
    if(mBrush) mBrush->Release();
}

void TextRenderer::Update() { }

void TextRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
    D2D1_POINT_2F position = mOwner->GetTransform()->GetPosition();
    D2D1_RECT_F layoutRect = D2D1::RectF(position.x, position.y, position.x + 300, position.y + 50);

    // 현재 변환 매트릭스를 저장
    D2D1_MATRIX_3X2_F originalTransform;
    renderTarget->GetTransform(&originalTransform);

    // 텍스트 렌더링 시 변환 매트릭스를 단순히 단위 행렬로 설정하여 텍스트가 뒤집히거나 변형되지 않도록 합니다.
    renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    renderTarget->DrawTextW(mText.c_str(), static_cast<UINT32>(mText.length()), mTextFormat, layoutRect, mBrush);

    // 원래 변환 매트릭스를 복원
    renderTarget->SetTransform(originalTransform);
}

void TextRenderer::SetText(const std::wstring& text) {
    mText = text;
}

void TextRenderer::SetColor(const D2D1_COLOR_F& color) {
    mColor = color;
    if(mBrush) {
        mBrush->SetColor(mColor);
    }
}

void TextRenderer::SetFontSize(float size) {
    mFontSize = size;
    if(mTextFormat) {
        mTextFormat->Release();
    }
    Renderer* renderer = Core::GetRenderer();
    renderer->GetDWriteFactory()->CreateTextFormat(
        L"Arial",
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        mFontSize,
        L"",
        &mTextFormat
    );
}
