#include "OverworldState.hpp"
#include "BattleState.hpp"
//#include "Game.hpp"

#include "../Objects/Graphic.hpp"

OverworldState::OverworldState(std::string filename, GameDataRef data) :
	BaseState(data)
{
    tmx::Map map;
    if(map.load("resources/data/maps/" + filename + ".tmx"))
    {
        /*const auto& layers = map.getLayers();
        for(int i = 0; i < layers.size(); i++) {
            mapLayers.push_back(MapLayer(map, i));
        }*/
        /*const auto& layers = map.getLayers();
        for(const auto& layer : layers)
        {
            std::cout << layer->getName() << "\n";
        }*/
        //const auto& layers = map.getLayers();
        const auto& layers = map.getLayers();
        for(int i = 0; i < layers.size(); i++) {
            const auto& layer = layers[i];
            if(layer->getType() == tmx::Layer::Type::Object) {
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                for(const auto& object : objects)
                {
                    //do stuff with object properties
                }
            } else if(layer->getType() == tmx::Layer::Type::Tile) {
                //const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                mapLayers.push_back(new MapLayer(map, i));
            } else if(layer->getType() == tmx::Layer::Type::Image) {
                //const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                mapLayers.push_back(new ImageLayer(map, i));
            }
        }

        const auto& c = map.getBackgroundColour();
        _color = sf::Color(c.r, c.g, c.b, c.a);

        _size = sf::Vector2i(map.getBounds().width, map.getBounds().height);

        for(const auto& property : map.getProperties()) {
            if(property.getName() == "repeatX") _repeatX = property.getBoolValue();
            if(property.getName() == "repeatY") _repeatY = property.getBoolValue();
        }
    }
}

void OverworldState::initState()
{
    sf::View view = this->_data->window->getView();
    view.move(0, 256);
    this->_data->window->setView(view);

    Graphic* face = new Graphic(&this->_data->assets, "resources/img/sprites/faces/sekai.png", 0);
    face->setUV(0, 0, 106, 106);
    face->setPosition(4, 16);
    addObject(face);
    addObject(new Graphic(&this->_data->assets, "resources/img/sprites/system/battle/player_box.png", 10));
}

void OverworldState::updateEvents(sf::Event e)
{
    sf::View v = this->_data->window->getView();
	switch (e.type) {
        case sf::Event::Closed:
            this->_data->window->close();
            break;
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Enter)
                this->_data->states.addState(Engine::StateRef(new BattleState(this->_data)), false);

            if (e.key.code == sf::Keyboard::Down)
                v.move(0, 32);
            if (e.key.code == sf::Keyboard::Up)
                v.move(0, -32);
            if (e.key.code == sf::Keyboard::Left)
                v.move(-32, 0);
            if (e.key.code == sf::Keyboard::Right)
                v.move(32, 0);
            this->_data->window->setView(v);
                
            break;
        default:
            break;
    }
}

// marks dt to not warn compiler
void OverworldState::updateState(float dt __attribute__((unused)))
{
    sf::Time duration = _clock.restart();

    std::vector<Layer*>::iterator itl = mapLayers.begin();
    while (itl != mapLayers.end()) {
        (*itl)->update(duration);
        itl++;
    }

    BaseState::updateState(dt);
}

// marks dt to not warn compiler
void OverworldState::drawState(float dt __attribute__((unused)))
{
	// background color
    this->_data->window->clear(_color);

    //std::cout << _repeatX << _repeatY << "\n";
    if(_repeatX || _repeatY) {
        sf::RenderTexture extendedMapTexture;;
        extendedMapTexture.create(_size.x, _size.y);
        
        std::vector<Layer*>::iterator itl = mapLayers.begin();
        while (itl != mapLayers.end()) {
            this->_data->window->draw(**itl);
            if((*itl)->getType() != LayerType::Image) {
                extendedMapTexture.draw(**itl);
            }
            itl++;
        }
        extendedMapTexture.display();

        sf::Sprite extendedMapSprite;
        extendedMapSprite.setTexture(extendedMapTexture.getTexture());
        
        sf::View view = this->_data->window->getView();
        sf::Vector2f viewCorner = view.getCenter();
        viewCorner -= view.getSize() / 2.f;

        int posX = static_cast<int>(std::floor(viewCorner.x / _size.x));
        int posY = static_cast<int>(std::floor(viewCorner.y / _size.y));
        int posX2 = static_cast<int>(std::ceil((viewCorner.x + view.getSize().x) / _size.x));
        int posY2 = static_cast<int>(std::ceil((viewCorner.y + view.getSize().y)/ _size.y));
        sf::IntRect repeatPos = sf::IntRect(posX, posY, posX2 - posX, posY2 - posY);
        /*if(!_repeatX) repeatPos.width = 1;
        if(!_repeatY) repeatPos.height = 1;*/
        for(int x = 0; x < repeatPos.width; x++) {
            for(int y = 0; y < repeatPos.height; y++) {
                if(!_repeatX && (x + repeatPos.left) != 0)
                    continue;
                if(!_repeatY && (y + repeatPos.top) != 0)
                    continue;
                if((x + repeatPos.left) == 0 && (y + repeatPos.top) == 0) {
                    continue;
                }

                extendedMapSprite.setPosition(_size.x * (x + repeatPos.left), _size.y * (y + repeatPos.top));
                this->_data->window->draw(extendedMapSprite);
            }
        }
    } else {
        std::vector<Layer*>::iterator itl = mapLayers.begin();
        while (itl != mapLayers.end()) {
            this->_data->window->draw(**itl);
            itl++;
        }
    }

    BaseState::drawState(dt);

	// Displays rendered obejcts
	this->_data->window->display();
}