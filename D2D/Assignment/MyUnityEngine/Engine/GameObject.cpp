#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject(const std::string& name) : mParent(nullptr), mName(name), mLayer(0) {
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

void GameObject::SetParent(GameObject* _parent) { 
    _parent->AddChild(this);
    mParent = _parent;
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

void GameObject::SetLayer(int layer) {
    mLayer = layer;
}

int GameObject::GetLayer() const {
    return mLayer;
}

AABB GameObject::GetAABB() const {
    D2D1_POINT_2F position = mTransform->GetPosition();
    D2D1_POINT_2F scale = mTransform->GetScale();

    AABB aabb;
    aabb.SetCenter(position.x, position.y);
    aabb.SetExtent(scale.x / 2.0f, scale.y / 2.0f);  // 크기 기준으로 AABB 확장 설정

    return aabb;
}