#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(const std::string& _name) : mName(_name) { }

GameObject::~GameObject() { }

void GameObject::Update() {
    for(auto& component : mComponents) {
        component->Update();
    }
}