#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <unordered_map>
#include <string>
#include "Renderer.h"

class ResourceManager {
public:
    static ResourceManager* GetInstance() {
        static ResourceManager instance;
        return &instance;
    }

    bool CreateD2DBitmapFromFile(const std::wstring& filePath);
    void ReleaseD2DBitmap(const std::wstring& strFilePath);
    ID2D1Bitmap* GetBitmap(const std::wstring& filePath);

    void ReleaseAllResources();

private:
    ResourceManager();
    ~ResourceManager();

    void SafeRelease(IUnknown* resource);

    std::unordered_map<std::wstring, ID2D1Bitmap*> mBitmapMap;
};