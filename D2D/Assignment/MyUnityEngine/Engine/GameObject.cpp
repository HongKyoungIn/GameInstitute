#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject(const std::string& name) : mName(name) {
    mTransform = new Transform(this);
    mComponents.push_back(mTransform); // Transform을 컴포넌트 리스트에 추가
}

GameObject::~GameObject() {
    // 컴포넌트를 삭제
    for(Component* component : mComponents) {
        delete component;
    }
    mComponents.clear(); // 컴포넌트 리스트를 비움
}

void GameObject::Update() {
    mTransform->Update();
    for(Component* component : mComponents) {
        component->Update();
    }
}

void GameObject::Render(ID2D1HwndRenderTarget* renderTarget) {
    for(Component* component : mComponents) {
        component->Render(renderTarget);
    }
}

void GameObject::AddChild(GameObject* child) {
    mChildren.push_back(child);
    child->GetTransform()->SetParent(mTransform); // 자식의 Transform에 부모 설정
}

void GameObject::RemoveChild(GameObject* child) {
    for(size_t i = 0; i < mChildren.size(); ++i) {
        if(mChildren[i] == child) {
            mChildren.erase(mChildren.begin() + i);
            delete child; // 자식을 삭제
            return;
        }
    }
}
