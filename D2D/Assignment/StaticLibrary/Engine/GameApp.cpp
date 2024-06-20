#include "pch.h"
#include "GameApp.h"

GameApp::GameApp() : m_hWnd(nullptr) { }

GameApp::~GameApp() {
    Uninitialize();
}

BOOL GameApp::Initialize(HINSTANCE hInstance, int nCmdShow) {
    if(!CreateMainWindow(hInstance, nCmdShow))
        return FALSE;
    if(!m_renderer.Initialize(m_hWnd))
        return FALSE;
    return TRUE;
}

void GameApp::Run() {
    MSG msg;
    while(TRUE) {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            m_renderer.BeginDraw();
            m_renderer.Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
            m_renderer.EndDraw();
        }
    }
}

void GameApp::Uninitialize() {
    m_renderer.Uninitialize();
}

LRESULT CALLBACK GameApp::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL GameApp::CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"GameAppClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if(!RegisterClassEx(&wcex))
        return FALSE;

    m_hWnd = CreateWindow(L"GameAppClass", L"Game App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if(!m_hWnd)
        return FALSE;

    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    return TRUE;
}
