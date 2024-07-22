#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "ResourceManager.h"

SpriteRenderer::SpriteRenderer(GameObject* owner)
	: Component(owner), mBitmap(nullptr), mDestRect(D2D1::RectF(0, 0, 100, 100)) { }

SpriteRenderer::~SpriteRenderer() {
    if(mBitmap) {
        mBitmap->Release();
        std::cout << "SpriteRenderer Release" << std::endl;
        Sleep(100);
        mBitmap = nullptr;
    }
}

void SpriteRenderer::SetBitMap(ID2D1Bitmap* _file) {
	mBitmap = _file;
}

void SpriteRenderer::SetSize(float width, float height) {
	mWidth = width;
	mHeight = height;
	mDestRect = D2D1::RectF(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);

    mOwner->SetAABBExtent(width, height);
}

void SpriteRenderer::Update() { }

bool SpriteRenderer::LoadBitmapFromFile(const std::wstring& filePath) {
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    if(resourceManager->CreateD2DBitmapFromFile(filePath)) {
        mBitmap = resourceManager->GetBitmap(filePath);
        return true;
    }
    return false;
}

void SpriteRenderer::Render(ID2D1HwndRenderTarget* renderTarget) {
    if(mBitmap) {
        Transform* transform = mOwner->GetTransform();
        D2D1_MATRIX_3X2_F worldTransform = transform->GetWorldTransform();

       // renderTarget->SetTransform(worldTransform);
        renderTarget->DrawBitmap(mBitmap, mDestRect);
        renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    }
}