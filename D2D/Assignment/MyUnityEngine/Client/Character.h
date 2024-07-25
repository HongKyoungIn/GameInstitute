#pragma once
#include "../Engine/Component.h"
#include "../Engine/FiniteStateMachine.h"
#include <d2d1.h>
#include <vector>

class Movement;

class Character : public Component {
public:
    enum Type {
        TYPE_HUMAN,
        TYPE_AI
    };

    enum StateID {
        STATE_STAND,
        STATE_MOVE,
        STATE_FOLLOW,
        STATE_ATTACK,
        STATE_RUNAWAY
    };

    enum Event {
        EVENT_FINDTARGET,
        EVENT_STOPWALK,
        EVENT_DUBIOUS,
        EVENT_BEATTACKED,
        EVENT_HEALTHDRAINED,
        EVENT_OUTOFATTACK,
        EVENT_WITHINATTACK,
        EVENT_LOSTTARGET
    };

    Character(GameObject* owner, Type _type, DWORD stateTransitions[][3], int numTransitions);
    ~Character();

    void Update() override;
    void Render(ID2D1HwndRenderTarget* renderTarget) override {};

    void SetDestPosition(D2D1_POINT_2F dest);
    D2D1_POINT_2F GetPosition() const { return position; }
    D2D1::ColorF GetColor() const;

    bool IsVisible(D2D1_POINT_2F pos);
    void Update(GameObject* target, float timeDelta);

private:
    void UpdateHuman(float timeDelta);
    void UpdateAI(GameObject* target, float timeDelta);

    void ActionStand(float timeDelta);
    void ActionMove(float timeDelta);
    void ActionFollow(float timeDelta);
    void ActionAttack(float timeDelta);
    void ActionRunaway(float timeDelta);

    void IssueEvent(DWORD event);
    void MoveTo(float timeDelta);

    Type type;
    FiniteStateMachine* stateMachine;
    D2D1_POINT_2F position;
    D2D1_POINT_2F destPosition;
    float orientation;
    float speed;
    float rangeView;
    float rangeTouch;
    D2D1::ColorF color;

    Movement* movement;
};

double GetLengthBetween(D2D1_POINT_2F p1, D2D1_POINT_2F p2);
