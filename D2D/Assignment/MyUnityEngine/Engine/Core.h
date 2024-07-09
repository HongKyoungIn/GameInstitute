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

	// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE, int);

private:
	// 윈도우 관련 변수,함수
	HINSTANCE mHInst; // 현재 인스턴스입니다.
	HWND mHWnd;
	WCHAR mSzTitle[MAX_LOADSTRING]; // 제목 표시줄 텍스트입니다.
	WCHAR mSzWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

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


// 디버깅을 위한 콘솔창 출력
private:
	void InitializeConsole(); // 콘솔 초기화 함수 추가

};