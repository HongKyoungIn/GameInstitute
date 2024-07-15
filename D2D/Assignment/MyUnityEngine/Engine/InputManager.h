#pragma once
#include <unordered_map>

enum class KeyState {
    None,
    Pressed,
    Held,
    Released
};

class InputManager {
public:
    static InputManager* GetInstance();
    static void DestroyInstance();

    void Update();
    void OnKeyDown(unsigned char key);
    void OnKeyUp(unsigned char key);
    bool IsKeyPressed(unsigned char key) const;
    bool IsKeyHeld(unsigned char key) const;
    bool IsKeyReleased(unsigned char key) const;

private:
    InputManager();
    ~InputManager();
    static InputManager* instance;

    std::unordered_map<unsigned char, KeyState> keyStates;
};
