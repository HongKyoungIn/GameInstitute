#pragma once
#include "CommonInclude.h"
#include "Component.h"
#include "Transform.h"
#include <vector>
#include <string>

class GameObject {
public:
    GameObject(const std::string& name);
    ~GameObject();

    void Update();
    void Render(ID2D1HwndRenderTarget* renderTarget);

    template <typename T, typename... TArgs>
    T* AddComponent(TArgs&&... args) {
        T* component = new T(this, std::forward<TArgs>(args)...);
        mComponents.push_back(component);
        return component;
    }

    template <typename T>
    T* GetComponent() {
        for(Component* component : mComponents) {
            T* comp = dynamic_cast<T*>(component);
            if(comp) {
                return comp;
            }
        }
        return nullptr;
    }

    Transform* GetTransform() const { return mTransform; }

    void AddChild(GameObject* child);
    void SetParent(GameObject* _parent);
    void RemoveChild(GameObject* child); // �ڽ� ������ ���� �޼��� �߰�
    const std::vector<GameObject*>& GetChildren() const { return mChildren; }

    const std::string& GetName() const {
        return mName;
    }

private:
    std::string mName;
    std::vector<Component*> mComponents;
    std::vector<GameObject*> mChildren; // �ڽ� GameObject�� �����ϴ� ����
    GameObject* mParent;
    Transform* mTransform;
};
