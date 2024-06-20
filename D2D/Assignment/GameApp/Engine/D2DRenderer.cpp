#include "D2DRenderer.h"

BOOL D2DRenderer::InitDirect2D(HWND hWnd) {
	// HRESULT Ÿ���� hr ������ S_OK (���� ���� �ڵ�)�� �ʱ�ȭ�մϴ�. 
	// �� ������ �Լ� ȣ���� ���� �Ǵ� ���� ���θ� �����ϴ� �� ���˴ϴ�.
	HRESULT hr = S_OK;


	// COM ��� ����
	// CoInitialize �Լ��� COM ���̺귯���� �ʱ�ȭ�մϴ�.
	// NULL�� �⺻ COINIT ���� ����϶�� ���Դϴ�.
	// �Լ� ȣ���� �����ϸ� hr�� ���� �ڵ带 �����ϰ�, FAILED ��ũ�θ� ���� ���и� Ȯ���Ͽ� FALSE�� ��ȯ�մϴ�.�̴� �Լ��� ���������� ��Ÿ���ϴ�.
	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return FALSE;


	/*	��ġ�� ���ε����� ���� ���ҽ��� ����ϴ�.������ ���� ���ӵǴ� ���� ȿ�������� ����˴ϴ�.
		�̷��� ���ҽ����� Direct2D �� DirectWrite ���͸���
		DirectWrite �ؽ�Ʈ ���� ��ü(Ư�� �۲� Ư���� �ĺ��ϴ� �� ����)�� ���Ե˴ϴ�.
	*/
	// D2D1CreateFactory �Լ��� Direct2D ���丮�� �����մϴ�.
	// D2D1_FACTORY_TYPE_SINGLE_THREADED�� ���丮�� ���� �����忡�� ���ȴٴ� ���� �ǹ��մϴ�.
	// & g_pD2DFactory�� ������ ���丮�� �����͸� ������ �����Դϴ�.
	// ���丮 ������ �����ϸ� FAILED ��ũ�θ� ���� Ȯ���ϰ�, FALSE�� ��ȯ�մϴ�.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
	if (FAILED(hr))
		return FALSE;


	/*
		Direct3D ��ġ�� ���ε��� ���ҽ��� ����ϴ�.
		Direct3D ��ġ�� �սǵ� ���(��: ���÷��� ����, ����, ���� ī�� ���� ��)
		���ҽ��� �ٽ� �����ؾ� �ϴ� ��츦 ����Ͽ� ��� ���⿡ �߾� ����ȭ�Ǿ� �ֽ��ϴ�.
	*/
	// GetClientRect �Լ��� g_hWnd �������� Ŭ���̾�Ʈ ���� ũ�⸦ ������ rc ����ü�� �����մϴ�.
	// RECT ����ü�� Ŭ���̾�Ʈ ������ ��ǥ�� �����մϴ�.
	RECT rc;
	GetClientRect(hWnd, &rc);


	// D2D1_SIZE_U ����ü�� ����Ͽ� Ŭ���̾�Ʈ ������ ũ�⸦ �����մϴ�.
	// SizeU �޼���� rc ����ü���� ���� �� ���� ũ�⸦ ����Ͽ� size ������ �����մϴ�.
	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);


	// Create a Direct2D render target.
	// Direct2D ���丮�� ����Ͽ� ���� Ÿ���� �����մϴ�.
	// D2D1::RenderTargetProperties()�� �⺻ ���� Ÿ�� �Ӽ��� �����մϴ�.
	// D2D1::HwndRenderTargetProperties(g_hWnd, size)�� ���� Ÿ���� ���ε��� ������ �ڵ�(g_hWnd)�� ũ��(size)�� �����մϴ�.
	// & g_pRenderTarget�� ������ ���� Ÿ���� �����͸� ������ �����Դϴ�.
	// �Լ� ȣ���� �����ϸ� FAILED ��ũ�θ� ���� Ȯ���ϰ�, FALSE�� ��ȯ�մϴ�.
	hr = g_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, size),
		&g_pRenderTarget);


	// ���� Ÿ�� ������ �����ߴ��� Ȯ���ϰ�, �����ϸ� FALSE�� ��ȯ�մϴ�.
	if (FAILED(hr))
		return FALSE;


	// ��� �ʱ�ȭ�� ���������� �Ϸ�Ǿ����� ��Ÿ���� ���� TRUE�� ��ȯ�մϴ�.
	return TRUE;

	// **����**
	// �� �Լ��� Direct2D�� ���������� �ʱ�ȭ�ϰ�, ���� Ÿ���� �����ϴ� �� ���˴ϴ�. 
	// �ʱ�ȭ �������� �߻��� �� �ִ� ���и� ó���ϸ�, ���������� �ʱ�ȭ�Ǹ� `TRUE`�� ��ȯ�մϴ�.

}

void D2DRenderer::UninitDirect2D() {
	if (g_pRenderTarget) g_pRenderTarget->Release();
	if (g_pD2DFactory) g_pD2DFactory->Release();

	// COM ��� ��
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