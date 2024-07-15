#include "Game1.h"
#include "../Engine/SpriteRenderer.h"
#include "../Engine/Transform.h"
#include "../Engine/Spinning.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Animator.h"
#include "../Engine/VideoMemoryDisplay.h"
#include "PlayerMove.h"

bool Game1::Initialize(_In_ HINSTANCE hInstance, _In_ int nCmdShow) {
	if(!Core::Initialize(hInstance, nCmdShow)) {
		return FALSE;
	}
	

	{
		// VRAM 사용량 출력
		GameObject* VRAM = new GameObject("VRAM");
		Transform* transform = VRAM->GetTransform();
		transform->SetPosition(60 , 10);
		transform->SetScale(2, 2);
		VRAM->SetLayer(2);  // UI 레이어

		VideoMemoryDisplay* videoMemoryDisplay = VRAM->AddComponent<VideoMemoryDisplay>();
		AddGameObject(VRAM);
	}

	{
		// 반전된 Run 애니메이션
		GameObject* player1 = new GameObject("Player1");
		Transform* transform = player1->GetTransform();
		transform->SetPosition(400, 400);
		// player1->SetLayer(1);  // 레이어 설정을 풀어서 배경화면에 뒤로 숨겨져 그려지지 않음.

		Animator* animator = player1->AddComponent<Animator>();
		animator->SetFlip(true);
		animator->SetAnimation(L"../Resource/Run.png", 10, 1, 0.1f);  // 8 frames, 0.1 seconds per frame
		animator->SetSize(100, 100);
		AddGameObject(player1);
	}

	{
		// 정상 Run 애니메이션
		GameObject* player2 = new GameObject("Player2");
		Transform* transform = player2->GetTransform();
		transform->SetPosition(500, 500);
		player2->SetLayer(1);  // 플레이어 레이어
		PlayerMove* playerMove = player2->AddComponent<PlayerMove>();

		Animator* animator = player2->AddComponent<Animator>();
		animator->SetAnimation(L"../Resource/Run.png", 10, 1, 0.1f);  // 8 frames, 0.1 seconds per frame
		animator->SetSize(100, 100);
		AddGameObject(player2);
	}

	{
		// 배경화면
		GameObject* Background = new GameObject("BackGround");
		Transform* transform = Background->GetTransform();
		transform->SetPosition(1920 / 2, 1080 / 2);
		Background->SetLayer(0);  // 배경 레이어

		Animator* animator = Background->AddComponent<Animator>();
		//animator->SetFlip(true);
		animator->SetAnimation(L"../Resource/midnight.png", 2, 2, 1.0f);  // 8 frames, 0.1 seconds per frame
		animator->SetSize(1920, 1080);
		AddGameObject(Background);
	}
	
	//{   // 부모 오브젝트 Sun 생성
	//	mPlayer1 = new GameObject("Sun");
	//	Transform* transform = mPlayer1->GetTransform();
	//	transform->SetPosition(1920.0f / 2, 1080.0f / 2);

	//	SpriteRenderer* spriteRenderer = mPlayer1->AddComponent<SpriteRenderer>();
	//	Spinning* spinning = mPlayer1->AddComponent<Spinning>(45.0f);
	//	spriteRenderer->LoadBitmapFromFile(L"../Resource/Sun.png");
	//	spriteRenderer->SetSize(300.0f, 300.0f);

	//	AddGameObject(mPlayer1);
	//}

	//{
	//	// Sun을 부모로 삼는 자식 오브젝트 Earth 생성
	//	mPlayer2 = new GameObject("Earth");
	//	Transform* transform = mPlayer2->GetTransform();
	//	transform->SetPosition(500.0f, 0.0f);

	//	SpriteRenderer* spriteRenderer = mPlayer2->AddComponent<SpriteRenderer>();
	//	Spinning* spinning = mPlayer2->AddComponent<Spinning>(90.0f);
	//	spriteRenderer->LoadBitmapFromFile(L"../Resource/Earth.png");
	//	spriteRenderer->SetSize(200.0f, 200.0f);

	//	mPlayer2->SetParent(mPlayer1);  // Player1을 부모로 설정

	//	AddGameObject(mPlayer2);
	//}
	//
	//{
	//	// Earth를 부모로 삼는 자식 오브젝트 Earth 생성
	//	GameObject* mPlayer3 = new GameObject("Moon");
	//	Transform* transform = mPlayer3->GetTransform();
	//	transform->SetPosition(150, 0);  // 부모 오브젝트로부터 상대적인 위치
	//	Spinning* spinning = mPlayer3->AddComponent<Spinning>(180.0f);

	//	SpriteRenderer* spriteRenderer = mPlayer3->AddComponent<SpriteRenderer>();
	//	spriteRenderer->LoadBitmapFromFile(L"../Resource/Moon.png");
	//	spriteRenderer->SetSize(100.0f, 100.0f);

	//	mPlayer3->SetParent(mPlayer2);  // Player1을 부모로 설정

	//	AddGameObject(mPlayer3);
	//}

	return true;
}

void Game1::Update() {
	Core::Update();
	HandleInput();  // 키 입력 처리 함수 호출
}

void Game1::FixedUpdate() {
	Core::FixedUpdate();
}

void Game1::Render() {
	Core::Render();
}

void Game1::CreateCharacter(D2D1_POINT_2F position, const std::wstring& filePath, int frameCountX, int frameCountY, float frameDuration) {
	GameObject* character = new GameObject("Character");
	Transform* transform = character->GetTransform();
	transform->SetPosition(position.x, position.y);

	Animator* animator = character->AddComponent<Animator>();
	animator->SetSize(100, 100);
	animator->SetAnimation(filePath, frameCountX, frameCountY, frameDuration);

	AddGameObject(character);
}

void Game1::HandleInput() {
	if((GetAsyncKeyState(VK_SPACE) & 0x8000) && !mSpacePressed) {
		mSpacePressed = true;
		D2D1_POINT_2F position = D2D1::Point2F((float)(rand() % 1920), (float)(rand() % 1080));
		CreateCharacter(position, L"../Resource/Run.png", 8, 1, 0.1f);
	}
	else if(!(GetAsyncKeyState(VK_SPACE) & 0x8000)) {
		mSpacePressed = false;
	}

	if(GetAsyncKeyState(VK_DELETE) & 0x8000 && !mDelPressed) {
		mDelPressed = true;
		if(!mGameObjects.empty()) {
			RemoveSpecificGameObject("Character");
		}
	}
	else if(!(GetAsyncKeyState(VK_DELETE) & 0x8000)) {
		mDelPressed = false;
	}
}