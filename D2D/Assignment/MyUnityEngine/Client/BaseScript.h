#pragma once
#include "../Engine/Component.h"

class BaseScript : public Component { 
	BaseScript(GameObject* owner) : Component(owner) { }

	virtual void Update() override;
	virtual void Render(ID2D1HwndRenderTarget* renderTarget) override { }
};

