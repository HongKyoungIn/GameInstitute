#include "Character.h"
#include "../Engine/GameObject.h"
#include <cmath>
#include "../Engine/TimeManager.h"
#include "../Engine/CircleRenderer.h"
#include "../Engine/Movement.h"
Character::Character(GameObject* owner, Type _type, DWORD stateTransitions[][3], int numTransitions)
    : Component(owner), type(_type), stateMachine(new FiniteStateMachine()), position{ 480, 300 }, orientation(0.0f), color(D2D1::ColorF(D2D1::ColorF::Black)) {

    // 유한 상태 기계를 생성합니다.
    for (int i = 0; i < numTransitions; i++) {
        stateMachine->AddStateTransition(stateTransitions[i][0], stateTransitions[i][1], stateTransitions[i][2]);
    }
    stateMachine->SetCurrentStateID(STATE_STAND);

    // 캐릭터 특성을 결정합니다.
    if (type == TYPE_AI) {
        rangeView = 300;
        speed = 300;
    }
    else {
        rangeView = 0;
        speed = 1000;
    }
    rangeTouch = 3.0f;

    // 초기화합니다.
    mOwner = owner;
    movement = mOwner->AddComponent<Movement>();
    position = D2D1::Point2F(480, 300);
    SetDestPosition(position);
}

Character::~Character() {
    if (stateMachine) {
        delete stateMachine;
    }
}

bool Character::IsVisible(D2D1_POINT_2F pos) {
    return GetLengthBetween(position, pos) < rangeView;
}

void Character::Update() {
    if (type == TYPE_HUMAN) {
        UpdateHuman(TimeManager::GetInstance()->GetDeltaTime());
    }
    
}

void Character::Update(GameObject* target, float DeltaTime) {
    if (type == TYPE_HUMAN) {
        UpdateHuman(DeltaTime);
    }
    else {
        UpdateAI(target, DeltaTime);
    }
}

void Character::UpdateHuman(float DeltaTime) {

    position = mOwner->GetComponent<Transform>()->GetPosition();
    switch (stateMachine->GetCurrentStateID()) {
    case STATE_STAND:
       /* if (GetLengthBetween(position, destPosition) >= 1.0f) {
            IssueEvent(EVENT_FINDTARGET);
            break;
        }*/
        ActionStand(DeltaTime);
        break;

    case STATE_MOVE:
        if (GetLengthBetween(position, destPosition) < 1.0f) {
            position = destPosition;
            IssueEvent(EVENT_STOPWALK);
            break;
        }
        ActionMove(DeltaTime);
        break;
    }
    //mOwner->GetComponent<Transform>()->SetPosition(position.x, position.y);
}

void Character::UpdateAI(GameObject* target, float DeltaTime) {
    
    position = mOwner->GetComponent<Transform>()->GetPosition();
    switch (stateMachine->GetCurrentStateID()) {
    case STATE_STAND:
        ActionStand(DeltaTime);
        if (target && IsVisible(target->GetComponent<Character>()->GetPosition())) {
            SetDestPosition(target->GetComponent<Character>()->GetPosition());
            IssueEvent(EVENT_FINDTARGET);
            break;
        }
        if ((GetTickCount64() % 10 == 0)) {
            D2D1_POINT_2F vt;
            vt.x = (float)(rand() % 640);
            vt.y = (float)(rand() % 480);
            SetDestPosition(vt);
            IssueEvent(EVENT_DUBIOUS);
            break;
        }
        break;

    case STATE_MOVE:
        ActionMove(DeltaTime);
        if (target && IsVisible(target->GetComponent<Character>()->GetPosition())) {
            SetDestPosition(target->GetComponent<Character>()->GetPosition());
            IssueEvent(EVENT_FINDTARGET);
            break;
        }
        if ((GetTickCount64() % 100 == 0) && (rand() % 10 < 2)) {
            
            IssueEvent(EVENT_STOPWALK);
            break;
        }
        break;

    case STATE_FOLLOW:
        if (target)
            SetDestPosition(target->GetComponent<Character>()->GetPosition());

        ActionFollow(DeltaTime);

        if (target && !IsVisible(target->GetComponent<Character>()->GetPosition())) {
            IssueEvent(EVENT_LOSTTARGET);
            break;
        }
        if (GetLengthBetween(position, destPosition) < 100.0f) {
            movement->SetSpeed(0);
            IssueEvent(EVENT_WITHINATTACK);
            break;
        }
        break;

    case STATE_ATTACK:
        if (target)
            SetDestPosition(target->GetComponent<Character>()->GetPosition());

        ActionAttack(DeltaTime);

        if (target && !IsVisible(target->GetComponent<Character>()->GetPosition())) {
            IssueEvent(EVENT_LOSTTARGET);
            break;
        }
        if (GetLengthBetween(position, destPosition) >= 100.0f) {
            IssueEvent(EVENT_OUTOFATTACK);
            break;
        }
        break;

    case STATE_RUNAWAY:
        ActionRunaway(DeltaTime);
        break;
    }

   //  mOwner->GetComponent<Transform>()->SetPosition(position.x, position.y);
}

void Character::ActionStand(float DeltaTime) {}

void Character::ActionMove(float DeltaTime) {
    MoveTo(DeltaTime);
}

void Character::ActionFollow(float DeltaTime) {
    MoveTo(DeltaTime);
}

void Character::ActionAttack(float DeltaTime) {}

void Character::ActionRunaway(float DeltaTime) {}

void Character::IssueEvent(DWORD event) {
    stateMachine->IssueEvent(event);

    switch (stateMachine->GetCurrentStateID()) {
    case STATE_STAND:
        color = D2D1::ColorF(D2D1::ColorF::White);
        break;
    case STATE_MOVE:
        color = D2D1::ColorF(D2D1::ColorF::Green);
        break;
    case STATE_ATTACK:
        color = D2D1::ColorF(D2D1::ColorF::Red);
        break;
    case STATE_FOLLOW:
        color = D2D1::ColorF(D2D1::ColorF::Blue);
        break;
    case STATE_RUNAWAY:
        color = D2D1::ColorF(D2D1::ColorF::Black);
        break;
    }
    mOwner->GetComponent<CircleRenderer>()->SetColor(color);
}

void Character::MoveTo(float deltaTime) {
    D2D1_POINT_2F toTarget = { destPosition.x - position.x, destPosition.y - position.y };
    float length = GetLengthBetween(position, destPosition);
    D2D1_POINT_2F direction = { toTarget.x / length, toTarget.y / length };

    movement->SetDirection(direction);
    movement->SetSpeed(speed);
}


void Character::SetDestPosition(D2D1_POINT_2F dest) {
    destPosition = dest;
    D2D1_POINT_2F toTarget = { destPosition.x - position.x, destPosition.y - position.y };
    if (GetLengthBetween(destPosition, position) < 30) 
        return;

    if (fabs(toTarget.x) >= 0.01 || fabs(toTarget.y) >= 0.01) {
        orientation = atan2(toTarget.x, toTarget.y);
    }
}

double GetLengthBetween(D2D1_POINT_2F p1, D2D1_POINT_2F p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
