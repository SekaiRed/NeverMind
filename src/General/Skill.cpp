#include "Skill.hpp"

//Skill::Skill(std::string name, std::string desc, int cost, EventChain (*execute)(BattleInstance* battle)) {
Skill::Skill(std::string name, std::string desc, int cost) {
    this->name = name;
    this->desc = desc;
    this->cost = cost;
}