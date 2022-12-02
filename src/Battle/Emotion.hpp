#pragma once

#include <string>

class Emotion {
    public:
        static Emotion NEUTRAL;
        //Happy
        static Emotion HAPPY;
        static Emotion ECTASTIC;
        static Emotion MANIC;
        //Sad
        static Emotion SAD;
        static Emotion DEPRESSED;
        static Emotion MISERABLE;
        //Angry
        static Emotion ANGRY;
        static Emotion ENRAGED;
        static Emotion FURIOUS;
        //Other
        static Emotion SCARED;
        static Emotion TOAST;

        static const int emotionCount = 12;
        static Emotion* emotions[12];

        int getBackgroundX();
        int getBackgroundY();
        int getFaceY();
        int getEmotionY();
        std::string getName();
        bool isSpecial();

    private:
        Emotion(std::string name, int sprBgX, int sprBgY, int sprCharY, int sprTextY, bool special = false);
        std::string name;
        int sprBgX, sprBgY, sprCharY, sprTextY;
        bool special;
};