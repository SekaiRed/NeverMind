#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <tmxlite/Map.hpp>
#include <tmxlite/Property.hpp>
#include <tmxlite/Types.hpp>

#include <string>
#include <vector>
#include <iostream>

typedef tmx::Layer::Type LayerType;

class Layer : public sf::Drawable {
public:
    Layer(const tmx::Map& map, std::size_t idx) {
        const auto& layers = map.getLayers();
        if (map.getOrientation() == tmx::Orientation::Orthogonal && idx < layers.size())
        {
            m_ID = idx;
            m_name = layers[idx]->getName();
            m_type = layers[idx]->getType();
            m_properties = layers[idx]->getProperties();
        }
        else
        {
            std::cout << "Not a valid orthogonal layer, nothing will be drawn." << std::endl;
        }
    }

    int getID() const { return m_ID; }
    std::string getName() const { return m_name; }
    const std::vector<tmx::Property>& getProperties() const { return m_properties; }
    virtual LayerType getType() const = 0;
    virtual void update(sf::Time elapsed) = 0;
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const = 0;

private:
    int m_ID;
    std::string m_name;
    LayerType m_type;
    std::vector<tmx::Property> m_properties;
};