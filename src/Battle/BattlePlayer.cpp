#include "BattlePlayer.hpp"

BattlePlayer::BattlePlayer(std::string name, std::string filename, int level, bool hasSpecialEmotion) {
    info = CharacterInfo(name, filename, hasSpecialEmotion);
    stats = CharacterStats(level);
    emotion = &Emotion::NEUTRAL;
    health = stats.getMaxHealth();
    juice = stats.getMaxJuice();
}

Emotion* BattlePlayer::getEmotion() {
    return emotion;
}
bool BattlePlayer::setEmotion(Emotion* emotion) {
    if(emotion == &Emotion::MANIC || emotion == &Emotion::MISERABLE || emotion == &Emotion::FURIOUS) {
        if(info.hasSpecialEmotion()) {
            this->emotion = emotion;
            return true;
        }

        return false;
    } else {
        this->emotion = emotion;
        return true;
    }
}
CharacterInfo* BattlePlayer::getInfo() {
    return &info;
}
CharacterStats* BattlePlayer::getStats() {
    return &stats;
}

void BattlePlayer::setHealth(int health) {
    this->health = health;
}
int BattlePlayer::getHealth() {
    return health;
}
void BattlePlayer::setJuice(int juice) {
    this->juice = juice;
}
int BattlePlayer::getJuice() {
    return juice;
}
