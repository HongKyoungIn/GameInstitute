#pragma once
#include "../Engine/Component.h"
#include "../Engine/InputManager.h"
#include "../Engine/TransForm.h"
#include "../Engine/GameObject.h"
#include "../Engine/Movement.h"

class PlayerMove : public Movement { 
public:
	PlayerMove(GameObject* owner) : Movement(owner) { }

	virtual void Update() override;
	virtual void Render(ID2D1HwndRenderTarget* renderTarget) override { }
};