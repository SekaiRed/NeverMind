#pragma once

#include <string>

class Skill {
    public:
        //Skill(std::string name, std::string desc, int cost, EventChain (*execute)(BattleInstance* battle));
        //void setSkill(std::string name, std::string desc, int cost, void (*execute)(EventChain* chain, BattleInstance* battle));
        //void (*execute)(EventChain* chain, BattleInstance* battle);
        Skill(std::string name, std::string desc, int cost);
    private:
        std::string name;
        std::string desc;
        int cost;
};

//Firesnow
//Annoy
//Curveball