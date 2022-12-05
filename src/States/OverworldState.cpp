#include "OverworldState.hpp"
#include "BattleState.hpp"
//#include "Game.hpp"

OverworldState::OverworldState(std::string filename, GameDataRef data) :
	_data(data)
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
    }
}

void OverworldState::initState()
{
    sf::View view = this->_data->window->getView();
    view.move(0, 256);
    this->_data->window->setView(view);
}

void OverworldState::updateEvents(sf::Event e)
{
    sf::View v = this->_data->window->getView();
	switch (e.type) {
        case sf::Event::Closed:
            this->_data->window->close();
            break;
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Escape)
                this->_data->window->close();
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
    sf::Time duration = globalClock.restart();

    std::vector<Layer*>::iterator itl = mapLayers.begin();
    while (itl != mapLayers.end()) {
        (*itl)->update(duration);
        itl++;
    }
}

// marks dt to not warn compiler
void OverworldState::drawState(float dt __attribute__((unused)))
{
	// just for fun, heres hello world text
	// SAMPLE RENDER CODE:

	// background color
    this->_data->window->clear(_color);

    /*std::vector<Layer*>::iterator itl = mapLayers.begin();
    while (itl != mapLayers.end()) {
        (*itl)->update(duration);
        this->_data->window->draw(**itl);
        itl++;
    }*/
    sf::RenderTexture tex;;
    tex.create(_size.x, _size.y);
    
    std::vector<Layer*>::iterator itl = mapLayers.begin();
    while (itl != mapLayers.end()) {
        //(*itl)->update(duration);
        //this->_data->window->getView().
        //(itl**)
        this->_data->window->draw(**itl);
        if((*itl)->getType() != LayerType::Image) {
            tex.draw(**itl);
        }
        itl++;
    }
    tex.display();

    sf::Sprite sprite1;
    sprite1.setTexture(tex.getTexture());
    
    /*sprite1.setPosition(_size.x, 0);
    this->_data->window->draw(sprite1);
    sprite1.setPosition(-_size.x, 0);
    this->_data->window->draw(sprite1);
    sprite1.setPosition(0, _size.y);
    this->_data->window->draw(sprite1);
    sprite1.setPosition(0, -_size.y);
    this->_data->window->draw(sprite1);*/
    sf::View view = this->_data->window->getView();
    sf::Vector2f viewCorner = view.getCenter();
    viewCorner -= view.getSize() / 2.f;

    int posX = static_cast<int>(std::floor(viewCorner.x / _size.x));
    int posY = static_cast<int>(std::floor(viewCorner.y / _size.y));
    int posX2 = static_cast<int>(std::ceil((viewCorner.x + view.getSize().x) / _size.x));
    int posY2 = static_cast<int>(std::ceil((viewCorner.y + view.getSize().y)/ _size.y));
    sf::IntRect repeatPos = sf::IntRect(posX, posY, posX2 - posX, posY2 - posY);
    for(int x = 0; x < repeatPos.width; x++) {
        for(int y = 0; y < repeatPos.height; y++) {
            //std::cout << "\033[31m" << _size.x * (x + repeatPos.left) << ", " << _size.y * (y + repeatPos.top) << "\n";
            if((x + repeatPos.left) == 0 && (y + repeatPos.top) == 0) {
                continue;
            }

            std::cout << _size.x * (x + repeatPos.left) << ", " << _size.y * (y + repeatPos.top) << "\n";
            sprite1.setPosition(_size.x * (x + repeatPos.left), _size.y * (y + repeatPos.top));
            this->_data->window->draw(sprite1);
        }
    }
    //std::cout << "repeatPos : " << repeatPos.left << ", " << repeatPos.top << " / " << repeatPos.width << ", " << repeatPos.height << "\n";
    //std::cout << "pos : " << posX << ", " << posY << " / " << posX2 << ", " << posY2 << "\n";

    //sf::FloatRect cameraRect();

    /*for (auto y = posY; y < posY2; ++y)
    {
        for (auto x = posX; x < posX2; ++x)
        {
            std::size_t idx = y * int(_size.x) + x;
            if (idx >= 0u && idx < m_chunks.size() && !m_chunks[idx]->empty())
            {
                //visible.push_back(m_chunks[idx].get());
            }
        }
    }*/

    
    /*drawWorld(0, 0);
    drawWorld(-_size.x, 0, true);
    drawWorld(_size.x, 0, true);
    drawWorld(0, -_size.y, true);
    drawWorld(0, _size.y, true);
    drawWorld(-_size.x, -_size.y, true);
    drawWorld(-_size.x, _size.y, true);
    drawWorld(_size.x, -_size.y, true);
    drawWorld(_size.x, _size.y, true);*/

	// Displays rendered obejcts
	this->_data->window->display();
}

/*void OverworldState::drawWorld(int offsetX, int offsetY, bool fake) {
    std::vector<Layer*>::iterator itl = mapLayers.begin();
    while (itl != mapLayers.end()) {
        //(*itl)->update(duration);
        //this->_data->window->getView().
        //(itl**)
        if(!((*itl)->getType() == LayerType::Image && fake)) {
            this->_data->window->draw(**itl);
        }
        itl++;
    }
}*/