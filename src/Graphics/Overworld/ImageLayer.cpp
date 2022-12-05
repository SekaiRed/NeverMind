#include "ImageLayer.hpp"

ImageLayer::ImageLayer(const tmx::Map& map, std::size_t idx) : Layer::Layer(map, idx) {
    const auto& layers = map.getLayers();
    if (map.getOrientation() == tmx::Orientation::Orthogonal &&
        idx < layers.size() && layers[idx]->getType() == tmx::Layer::Type::Image)
    {
        const auto& layer = layers[idx]->getLayerAs<tmx::ImageLayer>();

        imageTex.loadFromFile(layer.getImagePath());
        imageTex.setRepeated(true);
        
        for(const auto& property : layer.getProperties()) {
            if(property.getName() == "scrollX") scrollX = property.getFloatValue();
            if(property.getName() == "scrollY") scrollY = property.getFloatValue();
            if(property.getName() == "fixed") fixed = property.getBoolValue();
        }
    }
    else
    {
        std::cout << "Not a valid orthogonal layer, nothing will be drawn." << std::endl;
    }
}

LayerType ImageLayer::getType() const {
    return LayerType::Image;
}

void ImageLayer::update(sf::Time elapsed) {
    /*std::cout << imageTex.getSize().x << ", " << imageTex.getSize().y << "\n";
    std::cout << scrollX << ", " << scrollY << " : " << offsetX << ", " << offsetY << "\n";*/
    offsetX += elapsed.asSeconds() * scrollX;
    offsetY += elapsed.asSeconds() * scrollY;

    while(offsetX < 0)
        offsetX += imageTex.getSize().x;
    while(offsetX > imageTex.getSize().x)
        offsetX -= imageTex.getSize().x;

    while(offsetY < 0)
        offsetY += imageTex.getSize().y;
    while(offsetY > imageTex.getSize().y)
        offsetY -= imageTex.getSize().y;

    //imageSpr.setTextureRect();
}

void ImageLayer::draw(sf::RenderTarget& rt, sf::RenderStates states) const {
    sf::Sprite imageSpr;
    const sf::Vector2f position(
        rt.getView().getCenter().x - rt.getView().getSize().x/2,
        rt.getView().getCenter().y - rt.getView().getSize().y/2);

    imageSpr.setTexture(imageTex);
    imageSpr.setPosition(position);
    imageSpr.setTextureRect(sf::IntRect(
        offsetX + (fixed?0:position.x),
        offsetY + (fixed?0:position.y),
        rt.getView().getSize().x,
        rt.getView().getSize().y));

    rt.draw(imageSpr, states);
}