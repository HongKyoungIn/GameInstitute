#include "GameProject.h"

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
	GameProject project;

	if(project.Initialize(hInstance, nCmdShow) == FALSE) {
		return FALSE;
	}

	MSG msg;
	project.Loop(msg);

	project.Uninitialize();

	return (int)msg.wParam;
}