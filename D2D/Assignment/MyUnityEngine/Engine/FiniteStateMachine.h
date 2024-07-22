#pragma once
#include <windows.h>
#include <map>
#include <memory>
#include <iostream>

#define UNDEFINED 0

struct State {
    DWORD stateID;
    std::map<DWORD, DWORD> transitions; //(key,value)=(inputEvent,outputStateID)

    State(DWORD _stateID) : stateID(_stateID) { }
    ~State() { transitions.clear(); }

    DWORD getStateID() { return stateID; }
    DWORD getNumTransitions() { return transitions.size(); }

    void addTransition(DWORD inputEvent, DWORD outputStateID) {
        transitions[inputEvent] = outputStateID;
    }

    void deleteTransition(DWORD inputEvent) {
        transitions.erase(inputEvent);
    }

    DWORD getOutputStateID(DWORD inputEvent) {
        auto iter = transitions.find(inputEvent);
        if (iter == transitions.end()) {
            return UNDEFINED; // ��ϵ� ���̰� ����.
        }
        else {
            return iter->second;
        }
    }
};

class FiniteStateMachine {
private:
    std::map<DWORD, std::unique_ptr<State>> states; //(key,value)=(stateID, state object)
    DWORD currentStateID;

public:
    FiniteStateMachine() : currentStateID(UNDEFINED) { }
    ~FiniteStateMachine() { states.clear(); }

    void addStateTransition(DWORD stateID, DWORD inputEvent, DWORD outputStateID);

    void deleteTransition(DWORD stateID, DWORD inputEvent);

    void setCurrentStateID(DWORD stateID);

    void issueEvent(int inputEvent);

    DWORD getCurrentStateID() const { return currentStateID; }
};
