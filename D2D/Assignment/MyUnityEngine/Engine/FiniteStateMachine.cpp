#include "FiniteStateMachine.h"
#include <iostream>

void FiniteStateMachine::addStateTransition(DWORD stateID, DWORD inputEvent, DWORD outputStateID) {
    // ������ State�� �̹� �����ϴ����� �˾ƺ���.
    if (states.find(stateID) == states.end()) {
        states[stateID] = std::make_unique<State>(stateID); // �� ���¸� �����.
    }

    // ���� ���� ������ �߰��Ѵ�.
    states[stateID]->addTransition(inputEvent, outputStateID);
}

void FiniteStateMachine::deleteTransition(DWORD stateID, DWORD inputEvent) {
    auto iter = states.find(stateID);
    if (iter == states.end()) return; // ���°� ����.

    State* state = iter->second.get();
    // State�� ���� ������ �����.
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
    // �Է� �̺�Ʈ�� ���� �������̸� �����Ͽ� ���� ���¸� �ٲ�.
    if (currentStateID == UNDEFINED) return; // ���� ���°� ���ǵǾ� ���� ����.

    DWORD outputStateID = states[currentStateID]->getOutputStateID(inputEvent);
    if (outputStateID != UNDEFINED) {
        std::cout << "Transitioning from state " << currentStateID << " to state " << outputStateID << " on event " << inputEvent << std::endl;
        currentStateID = outputStateID; // ���� ���¸� �ٲ�.
    }
}
