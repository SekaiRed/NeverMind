#pragma once

//#include <SFML/Graphics.hpp>
#include "../Engine/AssetManager.hpp"
#include "AbstractRender.hpp"
//#include "../battle/emotion.hpp"

class SpriteRender : public AbstractRender {
    public:
        //InstanceRender(std::string filename/*, int u, int v, int uw, int uh*/);
        SpriteRender(Engine::AssetManager* man, std::string filename);
        virtual ~SpriteRender() {};
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void update();
        virtual bool destroy();
        void setPosition(float x, float y);
        void setOrigin(float x, float y);
        void setOffset(float offset_x, float offset_y);
        void setUV(int u, int v, int w, int h);
        //virtual void update(sf::RenderTarget& target, sf::RenderStates states) const;
    
    protected:
        //sf::Texture tex;
        sf::Sprite spr;
};