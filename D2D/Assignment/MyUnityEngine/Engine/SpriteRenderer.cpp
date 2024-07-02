#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Transform.h"

SpriteRenderer::SpriteRenderer(GameObject* owner)
	: Renderer(owner), mBitmap(nullptr), mDestRect(D2D1::RectF(0, 0, 100, 100)) { }

SpriteRenderer::~SpriteRenderer() {
	if(mBitmap) mBitmap->Release();
}

void SpriteRenderer::SetSize(float width, float height) {
	mWidth = width;
	mHeight = height;
	mDestRect = D2D1::RectF(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);
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

	IWICBitmapFrameDecode* pFrame = NULL;

	if(SUCCEEDED(hr)) {

		hr = pDecoder->GetFrame(0, &pFrame);
	}

	if(SUCCEEDED(hr)) {
		hr = mWICFactory->CreateFormatConverter(&pConverter);
	}

	if(SUCCEEDED(hr)) {
		hr = pConverter->Initialize(
			pFrame, GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone, NULL,
			0.f, WICBitmapPaletteTypeCustom
		);
	}

	if(SUCCEEDED(hr)) {
		hr = mRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &mBitmap);
	}

	if(pFrame) 
		pFrame->Release();

	if(pConverter) 
		pConverter->Release();

	if(pDecoder) 
		pDecoder->Release();

	return SUCCEEDED(hr);
}

void SpriteRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
	if(mBitmap) {
		Transform* transform = mOwner->GetTransform();
		D2D1_MATRIX_3X2_F worldTransform = transform->GetWorldTransform();

		renderTarget->SetTransform(worldTransform);
		renderTarget->DrawBitmap(mBitmap, mDestRect);
		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}