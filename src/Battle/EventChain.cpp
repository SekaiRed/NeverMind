#include "EventChain.hpp"
#include <iostream>

EventChain::~EventChain() {
    while(!events.empty()) {
        delete events.front();
        events.pop();
    }
}

void EventChain::addEvent(Event* event) {
    events.push(event);
}

void EventChain::tick(BattleState* battle) {
    //std::cout << timer << std::endl;
    if(events.empty()) {
        done = true; //Event chain is over!
    } else {
        //Event* event = events.front();
        Event* event = events.front();
        if(timer >= event->timer) {
            event->execute(battle);
            delete event;
            events.pop();
            timer = 0;
        } else {
            timer++;
        }
    }
    
}

bool EventChain::isDone() {
    return events.empty();
}

Event::Event(int timer) : timer(timer) {}
/*void Event::execute(BattleState* battle) {
    std::cout << "Event" << std::endl;
}*/

ShowNumberEvent::ShowNumberEvent(int timer, int amount, int c, int x, int y) : Event(timer), amount(amount) {
    this->c = c;
    this->x = x;
    this->y = y;
};
void ShowNumberEvent::execute(BattleState* battle) {
    //battle->addInstance(new NumberRender(amount, c, x, y));
    
    //battle->addInstance(new AnimationRender(&battle->getResources()->AUBREY_ATTACK_TEX, &battle->getResources()->AUBREY_ATTACK_ANIM, 2));//"resources/attack_big.png"
};

AnimationEvent::AnimationEvent(int timer, std::string ref, int speed, int x, int y) : Event(timer) {
    this->ref = ref;
    this->speed = speed;
    this->x = x;
    this->y = y;
};
void AnimationEvent::execute(BattleState* battle) {
    //std::cout << "AnimationEvent" << std::endl;
    /*AnimationRender* ani = new AnimationRender(tex, anim, speed);
    ani->setPosition(x, y);
    battle->addInstance(ani);//"resources/attack_big.png"*/
};

PlayerHurtEvent::PlayerHurtEvent(int timer, int player, int duration) : Event(timer) {
    this->player = player;
    this->duration = duration;
};
void PlayerHurtEvent::execute(BattleState* battle) {
    //box->hurt(duration);
    /*AnimationRender* ani = new AnimationRender(tex, anim, speed);
    ani->setPosition(x, y);
    battle->addInstance(ani);//"resources/attack_big.png"*/
};

PlayerForgotEvent::PlayerForgotEvent(int timer, int player, bool val) : Event(timer) {
    this->player = player;
    this->val = val;
};
void PlayerForgotEvent::execute(BattleState* battle) {
    //box->setForgot(val);
    /*AnimationRender* ani = new AnimationRender(tex, anim, speed);
    ani->setPosition(x, y);
    battle->addInstance(ani);//"resources/attack_big.png"*/
};

BattleLogEvent::BattleLogEvent(int timer, std::string text) : Event(timer) {
    this->text = text;
};
void BattleLogEvent::execute(BattleState* battle) {
    //battle->battleLog->push(text);
};
BattleLogClearEvent::BattleLogClearEvent(int timer) : Event(timer) {
};
void BattleLogClearEvent::execute(BattleState* battle) {
    //battle->battleLog->clear();
};