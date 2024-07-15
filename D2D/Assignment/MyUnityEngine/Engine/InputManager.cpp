#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance() {
    if(!instance) {
        instance = new InputManager();
    }
    return instance;
}

void InputManager::DestroyInstance() {
    if(instance) {
        delete instance;
        instance = nullptr;
    }
}

InputManager::InputManager() { }

InputManager::~InputManager() {
    keyStates.clear(); // Clear the key state map
}

void InputManager::Update() {
    for(auto& keyState : keyStates) {
        if(keyState.second == KeyState::Pressed) {
            keyState.second = KeyState::Held;
        }
        else if(keyState.second == KeyState::Released) {
            keyState.second = KeyState::None;
        }
    }
}

void InputManager::OnKeyDown(unsigned char key) {
    keyStates[key] = KeyState::Pressed;
}

void InputManager::OnKeyUp(unsigned char key) {
    keyStates[key] = KeyState::Released;
}

bool InputManager::IsKeyPressed(unsigned char key) const {
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second == KeyState::Pressed;
}

bool InputManager::IsKeyHeld(unsigned char key) const {
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second == KeyState::Held;
}

bool InputManager::IsKeyReleased(unsigned char key) const {
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second == KeyState::Released;
}
