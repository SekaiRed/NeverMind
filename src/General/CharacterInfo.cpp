#include "CharacterInfo.hpp"

CharacterInfo::CharacterInfo() {
    this->name = "Default";
    this->filename = "default";
}

CharacterInfo::CharacterInfo(std::string name, std::string filename, bool thirdStageEmotion) : thirdStageEmotion(thirdStageEmotion) {
    this->name = name;
    this->filename = filename;
}

std::string CharacterInfo::getName() {
    return name;
}

std::string CharacterInfo::getFilename() {
    return filename;
}

bool CharacterInfo::hasSpecialEmotion() {
    return thirdStageEmotion;
}
