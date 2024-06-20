#include "D2DRenderer.h"

BOOL D2DRenderer::InitDirect2D(HWND hWnd) {
	// HRESULT 타입의 hr 변수를 S_OK (성공 상태 코드)로 초기화합니다. 
	// 이 변수는 함수 호출의 성공 또는 실패 여부를 저장하는 데 사용됩니다.
	HRESULT hr = S_OK;


	// COM 사용 시작
	// CoInitialize 함수는 COM 라이브러리를 초기화합니다.
	// NULL은 기본 COINIT 값을 사용하라는 뜻입니다.
	// 함수 호출이 실패하면 hr에 실패 코드를 저장하고, FAILED 매크로를 통해 실패를 확인하여 FALSE를 반환합니다.이는 함수가 실패했음을 나타냅니다.
	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return FALSE;


	/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
		이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
		DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
	*/
	// D2D1CreateFactory 함수는 Direct2D 팩토리를 생성합니다.
	// D2D1_FACTORY_TYPE_SINGLE_THREADED는 팩토리가 단일 스레드에서 사용된다는 것을 의미합니다.
	// & g_pD2DFactory는 생성된 팩토리의 포인터를 저장할 변수입니다.
	// 팩토리 생성이 실패하면 FAILED 매크로를 통해 확인하고, FALSE를 반환합니다.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
	if (FAILED(hr))
		return FALSE;


	/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.
		Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
		리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
	*/
	// GetClientRect 함수는 g_hWnd 윈도우의 클라이언트 영역 크기를 가져와 rc 구조체에 저장합니다.
	// RECT 구조체는 클라이언트 영역의 좌표를 정의합니다.
	RECT rc;
	GetClientRect(hWnd, &rc);


	// D2D1_SIZE_U 구조체를 사용하여 클라이언트 영역의 크기를 저장합니다.
	// SizeU 메서드는 rc 구조체에서 가로 및 세로 크기를 계산하여 size 변수에 저장합니다.
	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);


	// Create a Direct2D render target.
	// Direct2D 팩토리를 사용하여 렌더 타겟을 생성합니다.
	// D2D1::RenderTargetProperties()는 기본 렌더 타겟 속성을 설정합니다.
	// D2D1::HwndRenderTargetProperties(g_hWnd, size)는 렌더 타겟이 바인딩될 윈도우 핸들(g_hWnd)과 크기(size)를 설정합니다.
	// & g_pRenderTarget는 생성된 렌더 타겟의 포인터를 저장할 변수입니다.
	// 함수 호출이 실패하면 FAILED 매크로를 통해 확인하고, FALSE를 반환합니다.
	hr = g_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, size),
		&g_pRenderTarget);


	// 렌더 타겟 생성이 실패했는지 확인하고, 실패하면 FALSE를 반환합니다.
	if (FAILED(hr))
		return FALSE;


	// 모든 초기화가 성공적으로 완료되었음을 나타내기 위해 TRUE를 반환합니다.
	return TRUE;

	// **설명**
	// 이 함수는 Direct2D를 성공적으로 초기화하고, 렌더 타겟을 생성하는 데 사용됩니다. 
	// 초기화 과정에서 발생할 수 있는 실패를 처리하며, 성공적으로 초기화되면 `TRUE`를 반환합니다.

}

void D2DRenderer::UninitDirect2D() {
	if (g_pRenderTarget) g_pRenderTarget->Release();
	if (g_pD2DFactory) g_pD2DFactory->Release();

	// COM 사용 끝
	CoUninitialize();
}

bool D2DRenderer::IsWindowFullscreen(HWND hWnd) {
	// Get the window style
	LONG style = GetWindowLong(hWnd, GWL_STYLE);

	// Check if the window has the fullscreen style
	return ((style & WS_POPUP) == WS_POPUP);
}

void D2DRenderer::EnterFullscreen(HWND hWnd) {
	// Retrieve the monitor handle
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

	// Get the monitor info
	MONITORINFO monitorInfo = { sizeof(monitorInfo) };
	GetMonitorInfo(hMonitor, &monitorInfo);

	// Set the window style
	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

	// Set the window position and size to cover the entire monitor
	SetWindowPos(hWnd, HWND_TOP, monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
		monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
		SWP_NOZORDER | SWP_FRAMECHANGED);
}

void D2DRenderer::ExitFullscreen(HWND hWnd) {
	// Set the window style back to its original state
	SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);

	// Restore the window position and size
	SetWindowPos(hWnd, HWND_TOP, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}