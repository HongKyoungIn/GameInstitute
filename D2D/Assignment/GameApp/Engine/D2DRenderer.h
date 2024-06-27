#pragma once
#include <d2d1.h>

class D2DRenderer {
public:
	BOOL InitDirect2D(HWND hWnd);
	void UninitDirect2D();
	static bool IsWindowFullscreen(HWND hWnd);
	static void EnterFullscreen(HWND hWnd);
	static void ExitFullscreen(HWND hWnd);

	ID2D1HwndRenderTarget* GetRenderTarget() {
		return mRenderTarget;
	}



private:

	//  D2D 개체 인터페이스 포인터 변수
	ID2D1Factory* mD2DFactory;
	ID2D1HwndRenderTarget* mRenderTarget;
};