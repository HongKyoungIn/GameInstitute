#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"

SpriteRenderer::SpriteRenderer(GameObject* owner)
	: Component(owner), mBitmap(nullptr), mDestRect(D2D1::RectF(0, 0, 100, 100)) { }

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

	Renderer* renderer = Core::GetRenderer();
	IWICImagingFactory* wicFactory = renderer->GetWICFactory();

	hr = wicFactory->CreateDecoderFromFilename(
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
		hr = wicFactory->CreateFormatConverter(&pConverter);
	}

	if(SUCCEEDED(hr)) {
		hr = pConverter->Initialize(
			pFrame, GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone, NULL,
			0.f, WICBitmapPaletteTypeCustom
		);
	}

	if(SUCCEEDED(hr)) {
		ID2D1HwndRenderTarget* renderTarget = renderer->GetRenderTarget();
		hr = renderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &mBitmap);
	}

	if(pFrame) 
		pFrame->Release();

	if(pConverter) 
		pConverter->Release();

	if(pDecoder) 
		pDecoder->Release();

	return SUCCEEDED(hr);
}

void SpriteRenderer::Update() { }

void SpriteRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
	if(mBitmap) {
		Transform* transform = mOwner->GetTransform();
		D2D1_MATRIX_3X2_F worldTransform = transform->GetWorldTransform();

		renderTarget->SetTransform(worldTransform);
		renderTarget->DrawBitmap(mBitmap, mDestRect);
		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}