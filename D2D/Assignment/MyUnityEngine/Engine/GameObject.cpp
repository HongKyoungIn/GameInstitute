#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject(const std::string& name) : mName(name) {
    mTransform = new Transform(this);
}

GameObject::~GameObject() {
    for(auto component : mComponents) {
        delete component;
    }
    for(auto child : mChildren) {
        delete child;
    }
    delete mTransform;
}

void GameObject::Update() {
    mTransform->Update();
    for(auto component : mComponents) {
        component->Update();
    }
    for(auto child : mChildren) {
        child->Update();
    }
}

void GameObject::Render(ID2D1HwndRenderTarget* renderTarget) {
    for(auto component : mComponents) {
        component->Render(renderTarget);
    }
    for(auto child : mChildren) {
        child->Render(renderTarget);
    }
}

void GameObject::AddChild(GameObject* child) {
    child->GetTransform()->SetParent(mTransform);
    mChildren.push_back(child);
}

void GameObject::RemoveChild(GameObject* child) {
    auto it = std::find(mChildren.begin(), mChildren.end(), child);
    if(it != mChildren.end()) {
        mChildren.erase(it);
        child->GetTransform()->SetParent(nullptr);
    }
}
