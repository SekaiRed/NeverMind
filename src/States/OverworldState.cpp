#include "OverworldState.hpp"

OverworldState::OverworldState(std::string filename, GameDataRef data) :
	BaseState(data)
{
    tmx::Map map;
    if(map.load("resources/data/maps/" + filename + ".tmx"))
    {
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

    Graphic* face = new Graphic(&this->_data->assets, "sprites/faces/sekai", 0);
    face->setUV(0, 0, 106, 106);
    face->setPosition(4, 16);
    addObject(face);
    addObject(new Graphic(&this->_data->assets, "sprites/system/battle/player_box", 10));

    player = new Graphic(&this->_data->assets, "sprites/characters/LILY", 5);
    player->setUV(32, 0, 32, 32);
    player->setPosition(32, 20);
    addObject(player);

    Animated* player_anim = new Animated(&this->_data->assets, "sprites/characters/DW_AUBREY", 8);
    player_anim->setUV(0, 0, 32, 32);
    player_anim->setPosition(128, 128);
    player_anim->assignAnimation("OW_WALK");
    addObject(player_anim);

    Animated* player_anim_run = new Animated(&this->_data->assets, "sprites/characters/DW_AUBREY_RUN", 8);
    player_anim_run->setUV(0, 0, 32, 32);
    player_anim_run->setPosition(128+64, 128);
    player_anim_run->assignAnimation("OW_RUN");
    addObject(player_anim_run);

    Animated* player_anim_spin = new Animated(&this->_data->assets, "sprites/characters/DW_HERO", 20);
    player_anim_spin->setUV(32, 0, 32, 32);
    player_anim_spin->setPosition(256, 256);
    player_anim_spin->assignAnimation("DEBUG_SPIN");
    addObject(player_anim_spin);

    Entity* big_anim = new Entity(&this->_data->assets, "sprites/characters/DW_PLAYGROUND_VAN", 4, {20, 8});
    big_anim->setUV(64, 0, 64, 64);
    //big_anim->setPosition(256, 256);
    big_anim->setWorldSize({1, 1});
    addObject(big_anim);

    Entity* lifejam_guy = new Entity(&this->_data->assets, "sprites/characters/lifejam_guy", 20, {19, 17});
    //lifejam_guy->setPosition(512, 512);
    lifejam_guy->setWorldSize({2, 2});
    lifejam_guy->assignAnimation("GEN_FLIP");
    addObject(lifejam_guy);

    Entity* lifejam_guy2 = new Entity(&this->_data->assets, "sprites/characters/lifejam_guy", 20, {33, 17});
    //lifejam_guy->setPosition(512, 512);
    lifejam_guy2->setWorldSize({2, 2});
    lifejam_guy2->assignAnimation("GEN_FLIP");
    addObject(lifejam_guy2);

    auto v = _data->window->getView();
    v.zoom(1.0f);
    _data->window->setView(v);
}

void OverworldState::updateEvents(sf::Event e)
{
    sf::View v = this->_data->window->getView();
	switch (e.type) {
        case sf::Event::MouseButtonPressed:
            if(sf::Mouse::Left == e.mouseButton.button) {
                sf::Vector2f target = this->_data->window->mapPixelToCoords({e.mouseButton.x, e.mouseButton.y});
                Animated* hey_anim = new Animated(&this->_data->assets, "sprites/animations/painful_truth", 8);
                hey_anim->setPosition(target.x, target.y);
                hey_anim->assignAnimation("BTL_PAINFUL_TRUTH");
                addObject(hey_anim);
            }
            break;
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
void OverworldState::updateState(sf::Time deltaTime)
{
    //sf::Time duration = _clock.restart();
    player->setZIndex(-player->getZIndex());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->_data->window->setFramerateLimit(60);
    } else {
        this->_data->window->setFramerateLimit(0);
    }

    std::vector<Layer*>::iterator itl = mapLayers.begin();
    while (itl != mapLayers.end()) {
        (*itl)->update(deltaTime);
        itl++;
    }

    BaseState::updateState(deltaTime);
}

// marks dt to not warn compiler
void OverworldState::drawState(sf::Time deltaTime)
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

    BaseState::drawState(deltaTime);

	// Displays rendered obejcts
	this->_data->window->display();
}