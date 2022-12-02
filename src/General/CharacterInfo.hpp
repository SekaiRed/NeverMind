#pragma once

#include <string>

class CharacterInfo {
    public:
        CharacterInfo();
        CharacterInfo(std::string name, std::string filename, bool thirdStageEmotion = false);
        std::string getName();
        std::string getFilename();
        bool hasSpecialEmotion();
    private:
        std::string name, filename;
        bool thirdStageEmotion;
};