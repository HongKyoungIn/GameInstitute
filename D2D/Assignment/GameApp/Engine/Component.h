#pragma once

class GameObject;

class Component {
public:
    Component(GameObject* owner);
    virtual ~Component();

    virtual void Update() = 0;

protected:
    GameObject* owner;
};
