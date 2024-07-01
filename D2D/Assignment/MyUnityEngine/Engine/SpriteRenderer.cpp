#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Transform.h"

SpriteRenderer::SpriteRenderer(GameObject* owner)
    : Renderer(owner), mBitmap(nullptr), mDestRect(D2D1::RectF(0, 0, 100, 100)) { }

SpriteRenderer::~SpriteRenderer() {
    if(mBitmap) mBitmap->Release();
}

void SpriteRenderer::SetSize(float width, float height) {
    mDestRect.right = mDestRect.left + width;
    mDestRect.bottom = mDestRect.top + height;
}

bool SpriteRenderer::LoadBitmapFromFile(const std::wstring& filePath) {
    HRESULT hr;
    IWICBitmapDecoder* pDecoder = NULL;
    IWICFormatConverter* pConverter = NULL;

    hr = mWICFactory->CreateDecoderFromFilename(
        filePath.c_str(),                  // Image to be decoded
        NULL,                              // Do not prefer a particular vendor
        GENERIC_READ,                      // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,    // Cache metadata when needed
        &pDecoder                          // Pointer to the decoder
    );

    if(SUCCEEDED(hr)) {
        IWICBitmapFrameDecode* pFrame = NULL;
        hr = pDecoder->GetFrame(0, &pFrame);
        if(SUCCEEDED(hr)) {
            hr = mWICFactory->CreateFormatConverter(&pConverter);
            if(SUCCEEDED(hr)) {
                hr = pConverter->Initialize(
                    pFrame, GUID_WICPixelFormat32bppPBGRA,
                    WICBitmapDitherTypeNone, NULL,
                    0.f, WICBitmapPaletteTypeCustom
                );
                if(SUCCEEDED(hr)) {
                    hr = mRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &mBitmap);
                }
            }
            if(pFrame) pFrame->Release();
        }
    }

    if(pConverter) pConverter->Release();
    if(pDecoder) pDecoder->Release();

    return SUCCEEDED(hr);
}

void SpriteRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
    if(mBitmap) {
        Transform* transform = mOwner->GetTransform();
        float x, y;
        transform->GetPosition(x, y);

        D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(x, y);
        D2D1_RECT_F destRect = mDestRect;
        D2D1_POINT_2F corners[4] = {
            {destRect.left, destRect.top},
            {destRect.right, destRect.top},
            {destRect.right, destRect.bottom},
            {destRect.left, destRect.bottom}
        };

        for(int i = 0; i < 4; ++i) {
            corners[i] = D2D1::Point2F(
                corners[i].x * translation._11 + corners[i].y * translation._21 + translation._31,
                corners[i].x * translation._12 + corners[i].y * translation._22 + translation._32
            );
        }

        destRect = D2D1::RectF(
            corners[0].x, corners[0].y,
            corners[2].x, corners[2].y
        );

        renderTarget->DrawBitmap(mBitmap, destRect);
    }
}
