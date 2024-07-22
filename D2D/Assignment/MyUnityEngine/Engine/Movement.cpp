#include "Movement.h"
#include "GameObject.h"

Movement::Movement(GameObject* Owner) : Component(Owner) {
	transform = mOwner->GetTransform();
}

void Movement::Update() {
	transform->SetPosition(transform->GetPosition().x + (mSpeed * mDirection.x) , 
		transform->GetPosition().y + (mSpeed * mDirection.y));
}

void Movement::Render(ID2D1HwndRenderTarget* renderTarget) { }
