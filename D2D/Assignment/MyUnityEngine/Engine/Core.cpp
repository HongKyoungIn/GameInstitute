// BasicD2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "Core.h"
#include "Renderer.h"
#include "GameObject.h"

Renderer* Core::mRenderer = nullptr; // 정적 멤버 변수 초기화

Core::Core() {
    InitializeConsole(); // 콘솔 창 초기화
    mRenderer = new Renderer();
    TimeManager::GetInstance()->Init();
}

Core::~Core() {
    Uninitialize();
}

bool Core::Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow) {
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, mSzTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ENGINE, mSzWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    if(!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    if(!mRenderer->InitDirect2D(mHWnd))
        return FALSE;

    return true;
}

void Core::Uninitialize() {
    for(GameObject* gameObject : mGameObjects) {
        delete gameObject;
    }
    mGameObjects.clear();

    if(mRenderer) {
        mRenderer->UninitDirect2D();
        delete mRenderer;
        mRenderer = nullptr;
    }
}

void Core::Loop(MSG& msg) {
    while(TRUE) {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT)
                break;

            //윈도우 메시지 처리 
            TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
            DispatchMessage(&msg);
        }
        else {
            TimeManager::GetInstance()->Update();
            Update();
            if(TimeManager::GetInstance()->ShouldFixedUpdate()) {
                FixedUpdate();
            }
            mRenderer->GetRenderTarget()->BeginDraw();
            mRenderer->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::Black));
            Render();

            mRenderer->GetRenderTarget()->EndDraw();
        }
    }
}

void Core::Update() {
    for(GameObject* gameObject : mGameObjects) {
        gameObject->Update();
    }
}

void Core::FixedUpdate() {
    // FixedUpdate가 필요한 경우, 이곳에 추가적인 업데이트 로직을 작성합니다.
}

void Core::Render() {
    for(GameObject* gameObject : mGameObjects) {
        gameObject->Render(mRenderer->GetRenderTarget());
    }
}

//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM Core::MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ENGINE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = mSzWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL Core::InitInstance(HINSTANCE hInstance, int nCmdShow) {
    mHInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    mHWnd = CreateWindowW(mSzWindowClass, mSzTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if(!mHWnd) {
        return FALSE;
    }

    ShowWindow(mHWnd, nCmdShow);
    UpdateWindow(mHWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {

    case WM_KEYDOWN:
        if(wParam == VK_F11) {
            // Toggle fullscreen mode
            if(Renderer::IsWindowFullscreen(hWnd))
                Renderer::ExitFullscreen(hWnd);
            else
                Renderer::EnterFullscreen(hWnd);
        }
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch(wmId) {
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void Core::AddGameObject(GameObject* gameObject) {
    mGameObjects.push_back(gameObject);
}

void Core::RemoveGameObject(GameObject* gameObject) {
    if(!gameObject) return;

    // 자식 오브젝트가 있다면 먼저 삭제
    const std::vector<GameObject*>& children = gameObject->GetChildren();
    for(size_t i = 0; i < children.size(); ++i) {
        RemoveGameObject(children[i]);  // 재귀적으로 자식 오브젝트 삭제
    }

    // 벡터에서 게임 오브젝트를 삭제
    for(size_t i = 0; i < mGameObjects.size(); ++i) {
        if(mGameObjects[i] == gameObject) {
            mGameObjects.erase(mGameObjects.begin() + i);
            delete gameObject;  // 게임 오브젝트 메모리 해제
            return;
        }
    }
}

void Core::InitializeConsole() {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);
    freopen_s(&file, "CONOUT$", "w", stderr);
    freopen_s(&file, "CONIN$", "r", stdin);
    std::cout << "Console window created" << std::endl;
}