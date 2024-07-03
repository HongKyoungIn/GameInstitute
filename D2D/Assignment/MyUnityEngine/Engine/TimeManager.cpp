#include "TimeManager.h"

void TimeManager::Init() {
    ::QueryPerformanceFrequency(&mFrequency);
    ::QueryPerformanceCounter(&mPrevCount);
    mLastFixedUpdateTime = mPrevCount;
}

void TimeManager::Update() {
    LARGE_INTEGER currentCount;
    ::QueryPerformanceCounter(&currentCount);

    mDeltaTime = (currentCount.QuadPart - mPrevCount.QuadPart) / static_cast<float>(mFrequency.QuadPart);
    mPrevCount = currentCount;

    //fps °è»ê
    mFrameCount++;
    mFrameTime += mDeltaTime;

    if(mFrameTime >= 1.f) {
        mFps = static_cast<unsigned int>(mFrameCount / mFrameTime);

        mFrameTime -= 1.f;
        mFrameCount = 0;
    }
}

bool TimeManager::ShouldFixedUpdate() {
    LARGE_INTEGER currentCount;
    ::QueryPerformanceCounter(&currentCount);

    float elapsedTime = (currentCount.QuadPart - mLastFixedUpdateTime.QuadPart) / static_cast<float>(mFrequency.QuadPart);
    if(elapsedTime >= mFixedDeltaTime) {
        mLastFixedUpdateTime = currentCount;
        return true;
    }
    return false;
}
