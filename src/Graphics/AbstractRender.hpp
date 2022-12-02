#pragma once

#include <SFML/Graphics.hpp>
/*#include "../src/Engine/AssetManager.hpp"

class Engine::AssetManager;*/

class AbstractRender : public sf::Drawable, public sf::Transformable {
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0; //const = 0;
        virtual void update() = 0;
        virtual bool destroy() = 0;
        AbstractRender(/*Engine::AssetManager* rsc*/) /*: rsc(rsc)*/ {};
        virtual ~AbstractRender() {};
        
    protected:
        float x, y, offset_x, offset_y; //origin_x and origin_y??? that could work as float 0->1
        //Engine::AssetManager* rsc;
};