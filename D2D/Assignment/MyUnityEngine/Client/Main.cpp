#include "Game1.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void f1() {
	_CrtDumpMemoryLeaks();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {

	atexit(f1);
	//_CrtSetBreakAlloc(210);
	Game1 app;

	if(app.Initialize(hInstance, nCmdShow) == FALSE) {
		return FALSE;
	}

	MSG msg;
	app.Loop(msg);

	app.Uninitialize();

	return (int)msg.wParam;
}