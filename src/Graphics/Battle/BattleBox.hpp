#pragma once

#include "../AbstractRender.hpp"
#include "../../Battle/BattlePlayer.hpp"
#include "../../Engine/AssetManager.hpp"
//#include "../battle/emotion.hpp"

class PlayerBoxRender : public AbstractRender {
    public:
        PlayerBoxRender(Engine::AssetManager* rsc, BattlePlayer* player);
        //void setEmotion(Emotion emotion);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void update();
        virtual bool destroy();
        void hurt(int duration = 30);
        void setForgot(bool val);
        float getWidth();
        float getHeight();
        bool isWithin(int x, int y);

    private:
        BattlePlayer* player;

        /*sf::Texture texFront;
        sf::Texture texBack;
        sf::Texture texFace;
        sf::Texture texText;
        sf::Texture texBar;*/
        sf::Sprite front;
        sf::Sprite back;
        sf::Sprite face;
        sf::Sprite text;
        sf::Sprite health;
        sf::Sprite juice;

        //sf::Font boxFont;
        sf::Text healthText;
        sf::Text healthTextWhite;
        sf::Text juiceText;
        sf::Text juiceTextWhite;

        //Emotion emotion = Emotion::NEUTRAL;
        //bool hasSpecialEmotion;
        int frame;
        int timer;
        int damaged_timer = 0;
        bool damaged = false;
        bool forgot = false;

        //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::IntRect getFaceRect();
        sf::IntRect getBgRect();
};