#pragma once

#include <string>
#include "Emotion.hpp"
#include "../General/CharacterInfo.hpp"
#include "../General/CharacterStats.hpp"

class BattlePlayer {
    public:
        BattlePlayer(std::string name, std::string filename, int level = 1, bool hasSpecialEmotion = false);
        Emotion* getEmotion();
        bool setEmotion(Emotion* emotion);
        CharacterInfo* getInfo();
        CharacterStats* getStats();
        void setHealth(int health);
        int getHealth();
        void setJuice(int juice);
        int getJuice();
        
    private:
        CharacterInfo info;
        CharacterStats stats;
        Emotion* emotion;
        int health, juice;
};