#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject(const std::string& name) : mName(name) {
    mTransform = new Transform(this);
}

GameObject::~GameObject() {
    for(Component* component : mComponents) {
        delete component;
    }
    for(GameObject* child : mChildren) {
        delete child;
    }
    delete mTransform;
}

void GameObject::Update() {
    mTransform->Update();
    for(Component* component : mComponents) {
        component->Update();
    }
    for(GameObject* child : mChildren) {
        child->Update();
    }
}

void GameObject::Render(ID2D1HwndRenderTarget* renderTarget) {
    for(Component* component : mComponents) {
        component->Render(renderTarget);
    }
    for(GameObject* child : mChildren) {
        child->Render(renderTarget);
    }
}

void GameObject::AddChild(GameObject* child) {
    mChildren.push_back(child);
    child->GetTransform()->SetParent(mTransform);
}
