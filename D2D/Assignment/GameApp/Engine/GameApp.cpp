// BasicD2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "GameApp.h"
#include "D2DRenderer.h"

GameApp::GameApp() {
	mD2DRenderer = new D2DRenderer;
}

GameApp::~GameApp() {

}

bool GameApp::Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow) {
	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GAMEAPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	if(!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	if(!mD2DRenderer->InitDirect2D(g_hWnd))
		return FALSE;

	return true;
}

void GameApp::UnInitalize() {
	mD2DRenderer->UninitDirect2D();
}

void GameApp::Loop(MSG& msg) {
	while(TRUE) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT)
				break;

			//윈도우 메시지 처리 
			TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);
		}
		else {
			Update();
			mD2DRenderer->GetRenderTarget()->BeginDraw();

			Render();
			mD2DRenderer->GetRenderTarget()->EndDraw();
		}
	}
}

void GameApp::Update() { }

void GameApp::Render() { }

//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM GameApp::MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEAPP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL GameApp::InitInstance(HINSTANCE hInstance, int nCmdShow) {
	g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if(!g_hWnd) {
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK GameApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {

	case WM_KEYDOWN:
		if(wParam == VK_F11) {
			// Toggle fullscreen mode
			if(D2DRenderer::IsWindowFullscreen(hWnd))
				D2DRenderer::ExitFullscreen(hWnd);
			else
				D2DRenderer::EnterFullscreen(hWnd);
		}
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch(wmId) {
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}