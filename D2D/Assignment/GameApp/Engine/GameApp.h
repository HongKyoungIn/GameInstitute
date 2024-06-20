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

	// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);

	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

private:
	// ������ ���� ����,�Լ�
	HINSTANCE g_hInst; // ���� �ν��Ͻ��Դϴ�.
	HWND g_hWnd;
	WCHAR szTitle[MAX_LOADSTRING]; // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING]; // �⺻ â Ŭ���� �̸��Դϴ�.

protected:
	D2DRenderer* d2dRenderer;
};