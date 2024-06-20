#include "DemoApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	
	DemoApp app;

	if (app.Initialize(hInstance, nCmdShow) == FALSE) {
		return FALSE;
	}

	MSG msg;
	app.Loop(msg);
	
	app.UnInitalize();

	return (int)msg.wParam;
}