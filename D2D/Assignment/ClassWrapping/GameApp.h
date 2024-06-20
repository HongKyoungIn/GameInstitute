#pragma once
#include <Windows.h>
#include "D2DRenderer.h"

class GameApp {
public:
    GameApp();
    ~GameApp();

    BOOL Initialize(HINSTANCE hInstance, int nCmdShow);
    void Run();
    void Uninitialize();

protected: // 접근 지정자를 protected로 변경
    HWND m_hWnd;
    D2DRenderer m_renderer;

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    BOOL CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
};
