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

    // ���� ��ȯ ��Ʈ������ ����
    D2D1_MATRIX_3X2_F originalTransform;
    renderTarget->GetTransform(&originalTransform);

    // �ؽ�Ʈ ������ �� ��ȯ ��Ʈ������ �ܼ��� ���� ��ķ� �����Ͽ� �ؽ�Ʈ�� �������ų� �������� �ʵ��� �մϴ�.
    renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    renderTarget->DrawTextW(mText.c_str(), static_cast<UINT32>(mText.length()), mTextFormat, layoutRect, mBrush);

    // ���� ��ȯ ��Ʈ������ ����
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
