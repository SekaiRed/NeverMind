#include "CharacterStats.hpp"

CharacterStats::CharacterStats(int level) {
    setLevel(level);
}

int CharacterStats::getAttack() {
    return attack;
}
int CharacterStats::getDefense() {
    return defense;
}
int CharacterStats::getSpeed() {
    return speed;
}
int CharacterStats::getLuck() {
    return luck;
}
int CharacterStats::getLevel() {
    return level;
}
void CharacterStats::setLevel(int level) {
    this->level = level;
    attack = 5;
    defense = 6;
    speed = 6;
    luck = 5;
    maxHealth = 33 + (6.24 * level);
    maxJuice = 20 + (4.6 * level);
}
int CharacterStats::getMaxHealth() {
    return maxHealth;
}
int CharacterStats::getMaxJuice() {
    return maxJuice;
}