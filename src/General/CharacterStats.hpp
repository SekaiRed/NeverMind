#pragma once

class CharacterStats {
    public:
        CharacterStats(int level = 1);
        int getAttack();
        int getDefense();
        int getSpeed();
        int getLuck();
        int getLevel();
        void setLevel(int level);
        int getMaxHealth();
        int getMaxJuice();

    private:
        int attack, defense, speed, luck, level, maxHealth, maxJuice;
};