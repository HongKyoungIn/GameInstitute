#pragma once
#include <d2d1.h>

class D2DRenderer
{
public:
	BOOL InitDirect2D(HWND hWnd);
	void UninitDirect2D();
	static bool IsWindowFullscreen(HWND hWnd);
	static void EnterFullscreen(HWND hWnd);
	static void ExitFullscreen(HWND hWnd);

	ID2D1HwndRenderTarget* GetRendererTarget() {
		return g_pRenderTarget;
	}



private:

	//  D2D ��ü �������̽� ������ ����
	ID2D1Factory* g_pD2DFactory;
	ID2D1HwndRenderTarget* g_pRenderTarget;
};

