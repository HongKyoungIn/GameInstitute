#pragma once

#include "CommonInclude.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TimeManager.h"

#define MAX_LOADSTRING 100

class Core {
// WindowAPI
public:
	Core();
	~Core();

	virtual bool Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow);
	void Uninitialize();
	void Loop(MSG& msg);

	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render();

	// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE, int);

private:
	// ������ ���� ����,�Լ�
	HINSTANCE mHInst; // ���� �ν��Ͻ��Դϴ�.
	HWND mHWnd;
	WCHAR mSzTitle[MAX_LOADSTRING]; // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR mSzWindowClass[MAX_LOADSTRING]; // �⺻ â Ŭ���� �̸��Դϴ�.

	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
// WindowAPI End

// Unity Engine
public:
	void AddGameObject(GameObject* gameObject);
	void RemoveGameObject(GameObject* _gameObject);

protected:
	std::vector<GameObject*> mGameObjects;

// D2DRenderer
protected:
	static Renderer* mRenderer;

public:
	static Renderer* GetRenderer() { return mRenderer; }


// ������� ���� �ܼ�â ���
private:
	void InitializeConsole(); // �ܼ� �ʱ�ȭ �Լ� �߰�

};