#include "OverworldState.hpp"
#include "BattleState.hpp"
//#include "Game.hpp"

OverworldState::OverworldState(std::string filename, GameDataRef data) :
	_data(data)
{
    tmx::Map map;
    if(map.load("resources/data/maps/" + filename))
    {
        /*const auto& layers = map.getLayers();
        for(int i = 0; i < layers.size(); i++) {
            mapLayers.push_back(MapLayer(map, i));
        }*/
        const auto& layers = map.getLayers();
        for(const auto& layer : layers)
        {
            std::cout << layer->getName() << "\n";
        }
        //layers = map.getLayers();
        /*const auto& layers = map.getLayers();
        for(const auto& layer : layers)
        {
            //layers.push_back(std::move(layer));
            if(layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                for(const auto& object : objects)
                {
                    //do stuff with object properties
                }
            }
            else if(layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                layers.push_back(MapLayer(layer.get()->));
                //read out tile layer properties etc...
            }
        }

        const auto& tilesets = map.getTilesets();
        for(const auto& tileset : tilesets)
        {
            //read out tile set properties, load textures etc...
        }*/
    }
}

void OverworldState::initState()
{
}

void OverworldState::updateEvents(sf::Event e)
{
	switch (e.type) {
        case sf::Event::Closed:
            this->_data->window->close();
            break;
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Escape)
                this->_data->window->close();
            if (e.key.code == sf::Keyboard::Enter)
                this->_data->states.addState(Engine::StateRef(new BattleState(this->_data)), false);
            break;
        default:
            break;
    }
}

// marks dt to not warn compiler
void OverworldState::updateState(float dt __attribute__((unused)))
{
}

// marks dt to not warn compiler
void OverworldState::drawState(float dt __attribute__((unused)))
{
	// just for fun, heres hello world text
	// SAMPLE RENDER CODE:

	// background color
	this->_data->window->clear(sf::Color::Black);

    sf::Time duration = globalClock.restart();
    /*layerZero.update(duration);

    window.clear(sf::Color::Black);
    window.draw(layerZero);
    window.draw(layerOne);
    window.draw(layerTwo);
    window.display();*/
    /*std::vector<MapLayer>::iterator itl = mapLayers.begin();
    while (itl != mapLayers.end()) {
        (*itl).update(duration);
        this->_data->window->draw(*itl);
    }*/

	// Displays rendered obejcts
	this->_data->window->display();
}