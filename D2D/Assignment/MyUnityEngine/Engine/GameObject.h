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
        for(auto component : mComponents) {
            T* comp = dynamic_cast<T*>(component);
            if(comp) {
                return comp;
            }
        }
        return nullptr;
    }

    void AddChild(GameObject* child);
    void RemoveChild(GameObject* child);

    Transform* GetTransform() const { return mTransform; }

private:
    std::string mName;
    std::vector<Component*> mComponents;
    std::vector<GameObject*> mChildren;
    Transform* mTransform;
};
