#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject(const std::string& name) : mName(name) {
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

void GameObject::RemoveChild(GameObject* child) {
    for(size_t i = 0; i < mChildren.size(); ++i) {
        if(mChildren[i] == child) {
            mChildren.erase(mChildren.begin() + i);
            delete child; // �ڽ��� ����
            return;
        }
    }
}
