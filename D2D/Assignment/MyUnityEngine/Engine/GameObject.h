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
    void RemoveChild(GameObject* child); // 자식 삭제를 위한 메서드 추가
    const std::vector<GameObject*>& GetChildren() const { return mChildren; }

    const std::string& GetName() const {
        return mName;
    }

private:
    std::string mName;
    std::vector<Component*> mComponents;
    std::vector<GameObject*> mChildren; // 자식 GameObject를 저장하는 벡터
    GameObject* mParent;
    Transform* mTransform;
};
