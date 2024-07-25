#include "TextRenderer.h"
#include "Core.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

TextRenderer::TextRenderer(GameObject* owner)
    : Component(owner), mText(L""), mFontSize(20.0f), mFontColor(D2D1::ColorF(D2D1::ColorF::Black)), mPosition(D2D1::Point2F(0, 0)) {
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
    renderer->GetRenderTarget()->CreateSolidColorBrush(mFontColor, &mBrush);
}

TextRenderer::~TextRenderer() {
    if (mTextFormat) mTextFormat->Release();
    if (mBrush) mBrush->Release();
}

void TextRenderer::Update() {
    // �ؽ�Ʈ ������Ʈ ������ �ʿ��� ��� �̰��� �ۼ�
}

void TextRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
    if (!mOwner || mText.empty()) return;

    Transform* transform = mOwner->GetTransform();
    D2D1_POINT_2F worldPosition = {
        transform->GetPosition().x + mPosition.x,
        transform->GetPosition().y + mPosition.y
    };

    IDWriteTextLayout* pTextLayout = nullptr;
    Renderer* renderer = Core::GetRenderer();
    renderer->GetDWriteFactory()->CreateTextLayout(
        mText.c_str(),
        (UINT32)mText.length(),
        mTextFormat,
        200.0f, // �ִ� �ʺ�
        50.0f,  // �ִ� ����
        &pTextLayout
    );

    DWRITE_TEXT_METRICS textMetrics;
    pTextLayout->GetMetrics(&textMetrics);

    float halfWidth = textMetrics.width / 2.0f;
    float halfHeight = textMetrics.height / 2.0f;

    D2D1_RECT_F layoutRect = D2D1::RectF(
        worldPosition.x - halfWidth,
        worldPosition.y - halfHeight,
        worldPosition.x + halfWidth,
        worldPosition.y + halfHeight
    );

    // �ؽ�Ʈ�� ������Ʈ�� �ø�(flip) ���¿� ������� ǥ�õǵ��� ��ȯ ��Ʈ������ ���� ��ķ� ����
    renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    renderTarget->DrawTextLayout(
        D2D1::Point2F(layoutRect.left, layoutRect.top),
        pTextLayout,
        mBrush
    );

    // �ؽ�Ʈ �ֺ��� �簢�� �׸��� (����׿�)
    ID2D1SolidColorBrush* borderBrush = nullptr;
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &borderBrush);
    renderTarget->DrawRectangle(layoutRect, borderBrush, 1.0f);
    borderBrush->Release();

    pTextLayout->Release();

    // ���� ��ȯ ��Ʈ������ ����
    D2D1_MATRIX_3X2_F worldTransform = transform->GetWorldTransform();
    renderTarget->SetTransform(worldTransform);
}

void TextRenderer::SetText(const std::wstring& text) {
    mText = text;
}

void TextRenderer::SetFontSize(float size) {
    mFontSize = size;
    UpdateTextFormat();
}

void TextRenderer::SetFontColor(D2D1_COLOR_F color) {
    mFontColor = color;
    if (mBrush) {
        mBrush->SetColor(color);
    }
}

void TextRenderer::SetPosition(D2D1_POINT_2F position) {
    mPosition = position;
}

void TextRenderer::UpdateTextFormat() {
    if (mTextFormat) {
        mTextFormat->Release();
    }

    Renderer* renderer = Core::GetRenderer();
    renderer->GetDWriteFactory()->CreateTextFormat(
        L"Arial", // ��Ʈ �̸�
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        mFontSize, // ��Ʈ ũ��
        L"", // ������
        &mTextFormat
    );
}
