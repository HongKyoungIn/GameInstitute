#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject(const std::string& name) : mParent(nullptr), mName(name), mLayer(0) {
    mTransform = new Transform(this);
    mComponents.push_back(mTransform); // Transform�� ������Ʈ ����Ʈ�� �߰�
}

GameObject::~GameObject() {
    // ������Ʈ�� ����
    for(Component* component : mComponents) {
        delete component;
    }
    mComponents.clear(); // ������Ʈ ����Ʈ�� ���
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
    child->GetTransform()->SetParent(mTransform); // �ڽ��� Transform�� �θ� ����
}

void GameObject::SetParent(GameObject* _parent) { 
    _parent->AddChild(this);
    mParent = _parent;
}

void GameObject::RemoveChild(GameObject* child) {
    for(size_t i = 0; i < mChildren.size(); ++i) {
        if(mChildren[i] == child) {
            mChildren.erase(mChildren.begin() + i);
            delete child; // �ڽ��� ����
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
    aabb.SetExtent(scale.x / 2.0f, scale.y / 2.0f);  // ũ�� �������� AABB Ȯ�� ����

    return aabb;
}