#include "FiniteStateMachine.h"
#include <iostream>

void FiniteStateMachine::addStateTransition(DWORD stateID, DWORD inputEvent, DWORD outputStateID) {
    // 동일한 State가 이미 존재하는지를 알아본다.
    if (states.find(stateID) == states.end()) {
        states[stateID] = std::make_unique<State>(stateID); // 새 상태를 만든다.
    }

    // 상태 전이 정보를 추가한다.
    states[stateID]->addTransition(inputEvent, outputStateID);
}

void FiniteStateMachine::deleteTransition(DWORD stateID, DWORD inputEvent) {
    auto iter = states.find(stateID);
    if (iter == states.end()) return; // 상태가 없음.

    State* state = iter->second.get();
    // State의 전이 정보를 지운다.
    state->deleteTransition(inputEvent);
    if (state->getNumTransitions() == 0) {
        states.erase(iter);
    }
}

void FiniteStateMachine::setCurrentStateID(DWORD stateID) {
    if (states.find(stateID) != states.end()) {
        currentStateID = stateID;
    }
}

void FiniteStateMachine::issueEvent(int inputEvent) {
    // 입력 이벤트에 따라서 상태전이를 수행하여 현재 상태를 바꿈.
    if (currentStateID == UNDEFINED) return; // 현재 상태가 정의되어 있지 않음.

    DWORD outputStateID = states[currentStateID]->getOutputStateID(inputEvent);
    if (outputStateID != UNDEFINED) {
        std::cout << "Transitioning from state " << currentStateID << " to state " << outputStateID << " on event " << inputEvent << std::endl;
        currentStateID = outputStateID; // 현재 상태를 바꿈.
    }
}
