#pragma once

#include "Object.hpp"
#include "../AssetManager.hpp"

class Graphic : public Object {
public:
    Graphic(Engine::AssetManager* man, std::string filename, int zIndex);
    virtual void update(sf::Time elapsed);
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;
    virtual sf::Transform getModifiedTransform() const;
    virtual int getZIndex();
    virtual void setSprite(Engine::AssetManager* man, std::string filename);
    virtual void setZIndex(int zIndex);
    virtual void setUV(int u, int v, int w, int h);
    virtual sf::FloatRect getBounds();
protected:
    sf::Sprite spr;
    int zIndex;
};