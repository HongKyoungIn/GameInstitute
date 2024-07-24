#include "Character.h"
#include "../Engine/GameObject.h"
#include "../Engine/TimeManager.h"
#include <cmath>

Character::Character(GameObject* owner, Type _type, DWORD stateTransitions[][3], int numTransitions)
    : Component(owner), type(_type), stateMachine(new FiniteStateMachine()), position{ 480, 300 }, orientation(0.0f), color(D2D1::ColorF(D2D1::ColorF::Black)) {
    for (int i = 0; i < numTransitions; i++) {
        stateMachine->addStateTransition(stateTransitions[i][0], stateTransitions[i][1], stateTransitions[i][2]);
    }
    stateMachine->setCurrentStateID(STATE_STAND);

    if (type == TYPE_AI) {
        rangeView = 100;
        speed = 80 + rand() % 3;
    }
    else {
        rangeView = 0;
        speed = 160;
    }
    rangeTouch = 3;

    setDestPosition(position);
}

Character::~Character() {
    if (stateMachine) {
        delete stateMachine;
    }
}

bool Character::isVisible(D2D1_POINT_2F pos) {
    return GetLengthBetween(position, pos) < rangeView;
}

void Character::Update() {
    if (type == TYPE_HUMAN) {
        updateHuman(TimeManager::GetInstance()->GetDeltaTime());
    }
    else {
        updateAI(nullptr, TimeManager::GetInstance()->GetDeltaTime());
    }
}

void Character::update(Character* target, float timeDelta) {
    if (type == TYPE_HUMAN) {
        updateHuman(timeDelta);
    }
    else {
        updateAI(target, timeDelta);
    }
}

void Character::updateHuman(float timeDelta) {
    switch (stateMachine->getCurrentStateID()) {
    case STATE_STAND:
        if (GetLengthBetween(position, destPosition) >= 1.0f) {
            issueEvent(EVENT_FINDTARGET);
            break;
        }
        actionStand(timeDelta);
        break;

    case STATE_MOVE:
        if (GetLengthBetween(position, destPosition) < 1.0f) {
            position = destPosition;
            issueEvent(EVENT_STOPWALK);
            break;
        }
        actionMove(timeDelta);
        break;
    }
}

void Character::updateAI(Character* target, float timeDelta) {
    switch (stateMachine->getCurrentStateID()) {
    case STATE_STAND:
        actionStand(timeDelta);
        if (target && isVisible(target->getPosition())) {
            setDestPosition(target->getPosition());
            issueEvent(EVENT_FINDTARGET);
            break;
        }
        if ((GetTickCount() % 10 == 0)) {
            D2D1_POINT_2F vt;
            vt.x = (float)(rand() % 640);
            vt.y = (float)(rand() % 480);
            setDestPosition(vt);
            issueEvent(EVENT_DUBIOUS);
            break;
        }
        break;

    case STATE_MOVE:
        actionMove(timeDelta);
        if (target && isVisible(target->getPosition())) {
            setDestPosition(target->getPosition());
            issueEvent(EVENT_FINDTARGET);
            break;
        }
        if ((GetTickCount() % 100 == 0) && (rand() % 10 < 2)) {
            issueEvent(EVENT_STOPWALK);
            break;
        }
        break;

    case STATE_FOLLOW:
        if (target) setDestPosition(target->getPosition());
        actionFollow(timeDelta);
        if (target && !isVisible(target->getPosition())) {
            issueEvent(EVENT_LOSTTARGET);
            break;
        }
        if (GetLengthBetween(position, destPosition) < 30.0f) {
            issueEvent(EVENT_WITHINATTACK);
            break;
        }
        break;

    case STATE_ATTACK:
        if (target) setDestPosition(target->getPosition());
        actionAttack(timeDelta);
        if (target && !isVisible(target->getPosition())) {
            issueEvent(EVENT_LOSTTARGET);
            break;
        }
        if (GetLengthBetween(position, destPosition) >= 30.0f) {
            issueEvent(EVENT_OUTOFATTACK);
            break;
        }
        break;

    case STATE_RUNAWAY:
        actionRunaway(timeDelta);
        break;
    }
}

void Character::actionStand(float timeDelta) { }

void Character::actionMove(float timeDelta) {
    moveTo(timeDelta);
}

void Character::actionFollow(float timeDelta) {
    moveTo(timeDelta);
}

void Character::actionAttack(float timeDelta) { }

void Character::actionRunaway(float timeDelta) { }

void Character::issueEvent(DWORD event) {
    stateMachine->issueEvent(event);
    switch (stateMachine->getCurrentStateID()) {
    case STATE_STAND:
        color = D2D1::ColorF(D2D1::ColorF::Black);
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
}

void Character::moveTo(float timeDelta) {
    D2D1_POINT_2F toTarget = { destPosition.x - position.x, destPosition.y - position.y };
    float length = GetLengthBetween(destPosition, position);
    position.x += timeDelta * speed * toTarget.x / length;
    position.y += timeDelta * speed * toTarget.y / length;
    if (length < 1) {
        issueEvent(EVENT_STOPWALK);
    }
}

void Character::setDestPosition(D2D1_POINT_2F dest) {
    destPosition = dest;
    D2D1_POINT_2F toTarget = { destPosition.x - position.x, destPosition.y - position.y };
    if (GetLengthBetween(destPosition, position) < 30) return;
    if (fabs(toTarget.x) >= 0.01 || fabs(toTarget.y) >= 0.01) {
        orientation = atan2(toTarget.x, toTarget.y);
    }
}

double GetLengthBetween(D2D1_POINT_2F p1, D2D1_POINT_2F p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
