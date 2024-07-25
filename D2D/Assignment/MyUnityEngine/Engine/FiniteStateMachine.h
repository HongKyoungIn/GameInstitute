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

    DWORD GetStateID() { return stateID; }
    DWORD GetNumTransitions() { return transitions.size(); }

    void AddTransition(DWORD inputEvent, DWORD outputStateID) {
        transitions[inputEvent] = outputStateID;
    }

    void DeleteTransition(DWORD inputEvent) {
        transitions.erase(inputEvent);
    }

    DWORD GetOutputStateID(DWORD inputEvent) {
        auto iter = transitions.find(inputEvent);
        if (iter == transitions.end()) {
            return UNDEFINED; // 등록된 전이가 없음.
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

    void AddStateTransition(DWORD stateID, DWORD inputEvent, DWORD outputStateID);

    void DeleteTransition(DWORD stateID, DWORD inputEvent);

    void SetCurrentStateID(DWORD stateID);

    void IssueEvent(int inputEvent);

    DWORD GetCurrentStateID() const { return currentStateID; }
};
