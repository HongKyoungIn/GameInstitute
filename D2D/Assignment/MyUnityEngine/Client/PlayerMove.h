#pragma once
#include "../Engine/Component.h"
#include "../Engine/InputManager.h"
#include "../Engine/TransForm.h"
#include "../Engine/GameObject.h"

class PlayerMove : public Component { 
public:
	PlayerMove(GameObject* owner) : Component(owner) { }

	virtual void Update() override;
	virtual void Render(ID2D1HwndRenderTarget* renderTarget) override { }
};