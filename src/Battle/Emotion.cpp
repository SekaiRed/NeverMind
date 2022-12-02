#include "Emotion.hpp"

Emotion::Emotion(std::string name, int sprBgX, int sprBgY, int sprCharY, int sprTextY, bool special) :
name(name), sprBgX(sprBgX), sprBgY(sprBgY), sprCharY(sprCharY), sprTextY(sprTextY), special(special) {}

int Emotion::getBackgroundX() {
    return sprBgX;
}

int Emotion::getBackgroundY() {
    return sprBgY;
}

int Emotion::getFaceY() {
    return sprCharY;
}

int Emotion::getEmotionY() {
    return sprTextY;
}

std::string Emotion::getName() {
    return name;
}

bool Emotion::isSpecial() {
    return special;
}

//Emotion::NEUTRAL = Emotion("Neutral", 0, 0);
Emotion Emotion::NEUTRAL("Neutral", 0, 0, 0, 0);

Emotion Emotion::HAPPY("Happy", 2, 0, 1, 1);
Emotion Emotion::ECTASTIC("Ectastic", 3, 0, 2, 2);
Emotion Emotion::MANIC("Manic", 0, 1, 11, 3, true);

Emotion Emotion::SAD("Sad", 1, 1, 4, 4);
Emotion Emotion::DEPRESSED("Depressed", 2, 1, 5, 5);
Emotion Emotion::MISERABLE("Miserable", 3, 1, 12, 6, true);

Emotion Emotion::ANGRY("Angry", 0, 2, 6, 7);
Emotion Emotion::ENRAGED("Enraged", 1, 2, 7, 8);
Emotion Emotion::FURIOUS("Furious", 2, 2, 13, 9, true);

Emotion Emotion::SCARED("Scared", 1, 0, 3, 10);
Emotion Emotion::TOAST("Toast", 3, 2, 8, -1);

Emotion* Emotion::emotions[12] = {
    &Emotion::NEUTRAL,
    &Emotion::HAPPY,
    &Emotion::ECTASTIC,
    &Emotion::MANIC,
    &Emotion::SAD,
    &Emotion::DEPRESSED,
    &Emotion::MISERABLE,
    &Emotion::ANGRY,
    &Emotion::ENRAGED,
    &Emotion::FURIOUS,
    &Emotion::SCARED,
    &Emotion::TOAST
};