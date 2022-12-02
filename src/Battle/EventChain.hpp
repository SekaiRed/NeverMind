#pragma once

#include "../States/BattleState.hpp"
#include <queue>

class BattleState;

struct Event {
    Event(int timer);
    virtual ~Event() {};
    int timer;
    virtual void execute(BattleState* battle) = 0;
};

class EventChain {
    public:
        ~EventChain();
        void addEvent(Event* event);
        void tick(BattleState* battle);
        bool isDone();
    private:
        int timer = 0;
        bool done = false;
        std::queue<Event*> events;
};

struct ShowNumberEvent : Event {
    ShowNumberEvent(int timer, int amount, int c, int x, int y);
    virtual ~ShowNumberEvent() {};
    int amount, c, x, y;
    void execute(BattleState* battle);
};

struct AnimationEvent : Event {
    AnimationEvent(int timer, std::string ref, int speed, int x, int y);
    virtual ~AnimationEvent() {};
    std::string ref;
    int speed, x, y;
    void execute(BattleState* battle);
};

struct PlayerHurtEvent : Event {
    PlayerHurtEvent(int timer, int player, int duration);
    virtual ~PlayerHurtEvent() {};
    int player;
    int duration;
    void execute(BattleState* battle);
};

struct PlayerForgotEvent : Event {
    PlayerForgotEvent(int timer, int player, bool val);
    virtual ~PlayerForgotEvent() {};
    int player;
    bool val;
    void execute(BattleState* battle);
};

struct BattleLogEvent : Event {
    BattleLogEvent(int timer, std::string text);
    virtual ~BattleLogEvent() {};
    std::string text;
    void execute(BattleState* battle);
};
struct BattleLogClearEvent : Event {
    BattleLogClearEvent(int timer);
    virtual ~BattleLogClearEvent() {};
    void execute(BattleState* battle);
};