#include "ResourceManager.h"
#include "Core.h"

ResourceManager::ResourceManager() { }

ResourceManager::~ResourceManager() {
    // ReleaseAllResources();
}

void ResourceManager::SafeRelease(IUnknown* resource) {
    if(resource) {
        resource->Release();
        resource = nullptr;  // 이 줄이 필요 없을 수 있습니다. 매개변수는 복사본입니다.
    }
}

bool ResourceManager::CreateD2DBitmapFromFile(const std::wstring& filePath) {
    if(mBitmapMap.find(filePath) != mBitmapMap.end()) {
        return true; // 이미 로드된 비트맵이 있음
    }

    HRESULT hr;
    IWICBitmapDecoder* pDecoder = nullptr;
    IWICFormatConverter* pConverter = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;
    ID2D1Bitmap* pBitmap = nullptr;

    Renderer* renderer = Core::GetRenderer();
    IWICImagingFactory* wicFactory = renderer->GetWICFactory();

    hr = wicFactory->CreateDecoderFromFilename(
        filePath.c_str(),
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnDemand,
        &pDecoder
    );

    if(SUCCEEDED(hr)) {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    if(SUCCEEDED(hr)) {
        hr = wicFactory->CreateFormatConverter(&pConverter);
    }

    if(SUCCEEDED(hr)) {
        hr = pConverter->Initialize(
            pFrame, GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone, nullptr,
            0.f, WICBitmapPaletteTypeCustom
        );
    }

    if(SUCCEEDED(hr)) {
        hr = renderer->GetRenderTarget()->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap);
    }

    SafeRelease(pConverter);
    SafeRelease(pFrame);
    SafeRelease(pDecoder);

    if(SUCCEEDED(hr)) {
        mBitmapMap[filePath] = pBitmap;
        return true;
    }

    return false;
}


void ResourceManager::ReleaseD2DBitmap(const std::wstring& strFilePath) {
    auto it = mBitmapMap.find(strFilePath);
    if(it != mBitmapMap.end()) {
        SafeRelease(it->second);
        mBitmapMap.erase(it);
    }
}

ID2D1Bitmap* ResourceManager::GetBitmap(const std::wstring& filePath) {
    auto it = mBitmapMap.find(filePath);
    if(it != mBitmapMap.end()) {
        return it->second;
    }
    return nullptr;
}

void ResourceManager::ReleaseAllResources() {
    std::cout << "Releasing all resources" << std::endl;

    mBitmapMap.clear();
}

AnimationAsset* ResourceManager::LoadAnimation(const std::wstring& filePath, int frameCount, float frameDuration) {
    auto it = mAnimations.find(filePath);
    if(it != mAnimations.end()) {
        it->second->AddRef();
        return it->second;
    }

    AnimationAsset* animation = new AnimationAsset();
    if(animation->Load(filePath, frameCount, frameDuration)) {
        mAnimations[filePath] = animation;
        animation->AddRef();
        return animation;
    }
    else {
        delete animation;
        return nullptr;
    }
}

void ResourceManager::ReleaseAnimation(const std::wstring& filePath) {
    auto it = mAnimations.find(filePath);
    if(it != mAnimations.end()) {
        it->second->Release();
        if(it->second->GetRefCount() == 0) {
            mAnimations.erase(it);
        }
    }
}