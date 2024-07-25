#include "FiniteStateMachine.h"
#include <iostream>

void FiniteStateMachine::AddStateTransition(DWORD stateID, DWORD inputEvent, DWORD outputStateID) {
    // ������ State�� �̹� �����ϴ����� �˾ƺ���.
    if (states.find(stateID) == states.end()) {
        states[stateID] = std::make_unique<State>(stateID); // �� ���¸� �����.
    }

    // ���� ���� ������ �߰��Ѵ�.
    states[stateID]->AddTransition(inputEvent, outputStateID);
}

void FiniteStateMachine::DeleteTransition(DWORD stateID, DWORD inputEvent) {
    auto iter = states.find(stateID);
    if (iter == states.end()) return; // ���°� ����.

    State* state = iter->second.get();
    // State�� ���� ������ �����.
    state->DeleteTransition(inputEvent);
    if (state->GetNumTransitions() == 0) {
        states.erase(iter);
    }
}

void FiniteStateMachine::SetCurrentStateID(DWORD stateID) {
    if (states.find(stateID) != states.end()) {
        currentStateID = stateID;
    }
}

void FiniteStateMachine::IssueEvent(int inputEvent) {
    // �Է� �̺�Ʈ�� ���� �������̸� �����Ͽ� ���� ���¸� �ٲ�.
    //if (currentStateID == UNDEFINED) return; // ���� ���°� ���ǵǾ� ���� ����.

    DWORD outputStateID = states[currentStateID]->GetOutputStateID(inputEvent);
    
    std::cout << "Transitioning from state " << currentStateID << " to state " << outputStateID << " on event " << inputEvent << std::endl;
    currentStateID = outputStateID; // ���� ���¸� �ٲ�.

}
