#pragma once

#include <Windows.h>

class TimeManager {
private:
    TimeManager() = default;

public:
    static TimeManager* GetInstance() {
        static TimeManager _instance;
        return &_instance;
    }

    void Init();
    void Update();

    unsigned int GetFps() { return mFps; }
    float GetDeltaTime() const { return mDeltaTime; }
    bool ShouldFixedUpdate();
    float GetFixedDeltaTime() const { return mFixedDeltaTime; }

private:
    unsigned int mFps = 0;
    unsigned int mFrameCount = 0;
    float mFrameTime = 0.f;

    LARGE_INTEGER mFrequency = { 0 };
    LARGE_INTEGER mPrevCount = { 0 };
    LARGE_INTEGER mCurCountFixed = { 0 };
    LARGE_INTEGER mLastFixedUpdateTime = { 0 };

    float mDeltaTime = 0.f;
    float mFixedDeltaTime = 0.02f; // 20ms fixed update interval. 50fps
};

