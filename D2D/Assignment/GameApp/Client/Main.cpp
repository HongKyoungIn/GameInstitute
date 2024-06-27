#include "DemoApp.h"
#include "../Engine/GameObject.h"
#include "../Engine/Transform.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {

	DemoApp app;

	if(app.Initialize(hInstance, nCmdShow) == FALSE) {
		return FALSE;
	}

	MSG msg;
	app.Loop(msg);

	app.UnInitalize();

	return (int)msg.wParam;

	GameObject player("Player");

	// Transform ������Ʈ�� �߰�
	Transform* transform = player.AddComponent<Transform>(100.f, 100.f);

	// ���� ������ �Ϻκ�
	while(true) {
		player.Update();
	}

	return 0;
}
