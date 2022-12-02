#include "BattleBox.hpp"

PlayerBoxRender::PlayerBoxRender(Engine::AssetManager* rsc, BattlePlayer* player) /*: AbstractRender(rsc)*/ {
    this->player = player;

    /*texFront.loadFromFile("resources/player_box.png");
    texFront.setRepeated(false);
    texFront.setSmooth(false);
    front.setTexture(texFront);*/
    front.setTexture(rsc->getTexture("resources/img/sprites/system/battle/player_box.png"));

    /*texBack.loadFromFile("resources/faceset_states.png");
    texBack.setRepeated(false);
    texBack.setSmooth(false);
    back.setTexture(texBack);*/
    back.setTexture(rsc->getTexture("resources/img/sprites/system/battle/faceset_states.png"));

    /*texFace.loadFromFile("resources/" + player->getInfo()->getFilename() + ".png");
    texFace.setRepeated(false);
    texFace.setSmooth(false);
    face.setTexture(texFace);*/
    face.setTexture(rsc->getTexture("resources/img/sprites/faces/" + player->getInfo()->getFilename() + ".png"));

    /*texText.loadFromFile("resources/emotion_text.png");
    texText.setRepeated(false);
    texText.setSmooth(false);
    text.setTexture(texText);*/
    text.setTexture(rsc->getTexture("resources/img/sprites/system/battle/emotion_text.png"));

    /*texBar.loadFromFile("resources/bar_gradients.png");
    texBar.setRepeated(false);
    texBar.setSmooth(false);
    health.setTexture(texBar);
    juice.setTexture(texBar);*/
    health.setTexture(rsc->getTexture("resources/img/sprites/system/battle/bar_gradients.png"));
    juice.setTexture(rsc->getTexture("resources/img/sprites/system/battle/bar_gradients.png"));

    //boxFont.loadFromFile("resources/fonts/OMORI_GAME2.ttf");
    healthText.setString("104/486");
    //healthText.setFont(boxFont);
    healthText.setFont(rsc->getFont("resources/fonts/OMORI_GAME2.ttf"));
    healthText.setFillColor(sf::Color::White);
    healthText.setOutlineColor(sf::Color(20, 20, 20));
    healthText.setOutlineThickness(1.1);
    //healthText.setCharacterSize(18);
    healthText.setCharacterSize(16);
    healthText.setOrigin(1, 0.5f);
    //healthText.setLineSpacing(0);
    //healthText.setStyle(sf::Text::Bold);

    healthTextWhite.setString("104/486");
    healthTextWhite.setFont(rsc->getFont("resources/fonts/OMORI_GAME2.ttf"));
    //healthTextWhite.setFont(boxFont);
    healthTextWhite.setFillColor(sf::Color::White);
    //juiceText.setOutlineColor(sf::Color::White);
    //juiceText.setOutlineThickness(0.2);
    //healthText.setCharacterSize(18);
    healthTextWhite.setCharacterSize(16);
    healthTextWhite.setOrigin(1, 0.5f);

    juiceText.setFont(rsc->getFont("resources/fonts/OMORI_GAME2.ttf"));
    //juiceText.setFont(boxFont);
    juiceText.setFillColor(sf::Color::White);
    juiceText.setOutlineColor(sf::Color(20, 20, 20));
    juiceText.setOutlineThickness(1.1);
    //healthText.setCharacterSize(18);
    juiceText.setCharacterSize(16);
    juiceText.setOrigin(1, 0.5f);
    //healthText.setLineSpacing(0);
    //healthText.setStyle(sf::Text::Bold);

    juiceTextWhite.setString("104/486");
    juiceTextWhite.setFont(rsc->getFont("resources/fonts/OMORI_GAME2.ttf"));
    //juiceTextWhite.setFont(boxFont);
    juiceTextWhite.setFillColor(sf::Color::White);
    //juiceText.setOutlineColor(sf::Color::White);
    //juiceText.setOutlineThickness(0.2);
    //healthText.setCharacterSize(18);
    juiceTextWhite.setCharacterSize(16);
    juiceTextWhite.setOrigin(1, 0.5f);

    /*sf::Font font;
    if (!font.loadFromFile("resources/fonts/OMORI_GAME2.ttf")) {}
    sf::Text text;
    text.setPosition(W_W/2 - 356/2 + 16, 0);
    text.setFont(font); // font is a sf::Font
    text.setString("What will SEKAI and friends do?");
    text.setCharacterSize(22); // in pixels, not points!*/

    timer = 0;
    frame = 0;
}

float PlayerBoxRender::getWidth() {
    return front.getGlobalBounds().width;
}
float PlayerBoxRender::getHeight() {
    return front.getGlobalBounds().height;
}

bool PlayerBoxRender::isWithin(int x, int y) {
    return (x > getPosition().x && x < getPosition().x + getWidth() && y > getPosition().y && y < getPosition().y + getHeight());
}

void PlayerBoxRender::hurt(int timer) {
    damaged_timer = timer;
    damaged = true;
}

void PlayerBoxRender::setForgot(bool value) {
    forgot = value;
}

void PlayerBoxRender::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    sf::Transform faceTransform = sf::Transform(states.transform);
    //faceTransform.translate(4, 14);
    //faceTransform.translate(4, 20);
    faceTransform.translate(4, 16);

    sf::Transform bgTransform = sf::Transform(states.transform);
    bgTransform.translate(7, 17);

    sf::Transform textTransform = sf::Transform(states.transform);
    textTransform.translate(7, 5);

    sf::Transform barTransform = sf::Transform(states.transform);
    barTransform.translate(28, 127);

    sf::Transform barTransform2 = sf::Transform(states.transform);
    barTransform2.translate(28, 127 + 19);

    sf::Transform healthTextTransform = sf::Transform(states.transform);
    //healthTextTransform.translate(109, 133);
    //healthTextTransform.translate(54, 120);
    healthTextTransform.translate(107 - healthText.getGlobalBounds().width, 127 - healthText.getGlobalBounds().height/2);

    sf::Transform juiceTextTransform = sf::Transform(states.transform);
    //healthTextTransform.translate(109, 133);
    //healthTextTransform.translate(54, 120);
    juiceTextTransform.translate(107 - juiceText.getGlobalBounds().width, 127 - juiceText.getGlobalBounds().height/2 + 19);

    target.draw(back, bgTransform);
    target.draw(face, faceTransform);
    target.draw(front, states);
    target.draw(text, textTransform);
    target.draw(health, barTransform);
    target.draw(juice, barTransform2);
    target.draw(healthText, healthTextTransform);
    target.draw(healthTextWhite, healthTextTransform);
    target.draw(juiceText, juiceTextTransform);
    target.draw(juiceTextWhite, juiceTextTransform);
}

void PlayerBoxRender::update() {
    timer++;
    if(timer>12) {
        timer=0;
        frame++;
        if(frame>2) {
            frame = 0;
        }
    }

    if(damaged) {
        damaged_timer--;
        if(damaged_timer == 0) {
            damaged = false;
        }
    }

    //todo change the method to fetch sprite x and y
    /*if(!damaged)
        face.setTextureRect(sf::IntRect(frame * 106, player->getEmotion()->getFaceY() * 106, 106, 106));
    else
        face.setTextureRect(sf::IntRect(frame * 106, 954, 106, 106));*/
    face.setTextureRect(getFaceRect());
    //back.setTextureRect(sf::IntRect(player->getEmotion()->getBackgroundX() * 100, player->getEmotion()->getBackgroundY() * 100, 100, 100));
    back.setTextureRect(getBgRect());
    text.setTextureRect(sf::IntRect(0, player->getEmotion()->getEmotionY() * 18, 100, 18));
    health.setTextureRect(sf::IntRect(0, 0, (int) (81.0 * ((double)player->getHealth() / (double)player->getStats()->getMaxHealth())), 12));
    juice.setTextureRect(sf::IntRect(0, 19, (int) (81.0 * ((double)player->getJuice() / (double)player->getStats()->getMaxJuice())), 12));

    //Make this only apply when health changes
    std::string h_s = std::to_string(player->getHealth()) + "/" + std::to_string(player->getStats()->getMaxHealth());
    healthText.setString(h_s);
    healthTextWhite.setString(h_s);

    std::string h_j = std::to_string(player->getJuice()) + "/" + std::to_string(player->getStats()->getMaxJuice());
    juiceText.setString(h_j);
    juiceTextWhite.setString(h_j);
}

bool PlayerBoxRender::destroy() {
    return false;
}

sf::IntRect PlayerBoxRender::getFaceRect() {
    if(damaged)
        return sf::IntRect(frame * 106, 9 * 106, 106, 106);
    
    if(forgot)
        return sf::IntRect(frame * 106, 14 * 106, 106, 106);

    return sf::IntRect(frame * 106, player->getEmotion()->getFaceY() * 106, 106, 106);
}

sf::IntRect PlayerBoxRender::getBgRect() {
    if(forgot)
        return sf::IntRect(0, 3 * 100, 100, 100);

    return sf::IntRect(player->getEmotion()->getBackgroundX() * 100, player->getEmotion()->getBackgroundY() * 100, 100, 100);
}