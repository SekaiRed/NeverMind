#pragma once

#include "Object.hpp"
#include "../Engine/AssetManager.hpp"

class Graphic : public Object {
public:
    Graphic(Engine::AssetManager* man, std::string filename, int zIndex);
    virtual void update(sf::Time elapsed);
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;
    virtual sf::Transform getModifiedTransform() const;
    virtual int getZIndex();
    virtual void setUV(int u, int v, int w, int h);
protected:
    sf::Sprite spr;
    int zIndex;
};