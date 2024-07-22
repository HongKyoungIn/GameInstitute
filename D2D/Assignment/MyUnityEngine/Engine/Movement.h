#pragma once
#include "Component.h"

class Transform;

class Movement : public Component { 
public:
	Movement(GameObject* Owner) ;
	~Movement() { }

	virtual void Update() override;
	virtual void Render(ID2D1HwndRenderTarget* renderTarget) override;

	void SetDirection(D2D1_POINT_2F _direction) { mDirection = _direction; }
	void SetSpeed(float _speed) { mSpeed = _speed; }

private:
	Transform* transform;
	D2D1_POINT_2F mDirection;
	float mSpeed;
};