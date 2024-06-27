#pragma once

#include <vector>
#include <string>
#include <memory>

class Component;

class GameObject {
public:
    GameObject(const std::string& name);
    ~GameObject();

    void Update();

    template <typename T, typename... TArgs>
    T* AddComponent(TArgs&&... args) {
        T* component = new T(this, std::forward<TArgs>(args)...);
        mComponents.emplace_back(component);
        return component;
    }

    template <typename T>
    T* GetComponent() {
        for(auto& component : mComponents) {
            T* comp = dynamic_cast<T*>(component.get());
            if(comp) {
                return comp;
            }
        }
        return nullptr;
    }

private:
    std::string mName;
    std::vector<std::unique_ptr<Component>> mComponents;
};