#pragma once

#include "resource.h"
#include <d2d1.h>

#define MAX_LOADSTRING 100

class D2DRenderer;

class GameApp {

public:
	GameApp();
	~GameApp();

	bool Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow);
	void UnInitalize();
	void Loop(MSG& msg);

	virtual void Update();
	virtual void Render();

	// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

private:
	// 윈도우 관련 변수,함수
	HINSTANCE g_hInst; // 현재 인스턴스입니다.
	HWND g_hWnd;
	WCHAR szTitle[MAX_LOADSTRING]; // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

protected:
	D2DRenderer* d2dRenderer;
};