#pragma once

#include <SFML/Graphics.hpp>
#include "../../Graphics/SpriteRender.hpp"
#include "../../Engine/AssetManager.hpp"
//#include "../battle/battle_player.hpp"

class EnemyRender : public SpriteRender {
    public:
        EnemyRender(Engine::AssetManager* man, std::string filename);
        //void setEmotion(Emotion emotion);
        //void update(sf::Time elapsed);
        float getWidth();
        float getHeight();
        //void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void update();

    private:
        /*sf::Texture texEnemy;
        sf::Sprite sprEnemy;*/
        int frame;
        int timer;
};