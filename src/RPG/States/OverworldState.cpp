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
    player = new Actor(&this->_data->assets, "sprites/characters/DW_AUBREY", 1, this);
    player->setWorldPos({1,1});
    player->setIdleAnimation("OW_IDLE");
    player->setWalkAnimation("OW_WALK");
    player->setUV(32, 0, 32, 33);
    addEntity(player);

    Entity* player_anim_run = new Entity(&this->_data->assets, "sprites/characters/DW_AUBREY_RUN", 8);
    player_anim_run->setUV(0, 0, 32, 33);
    //player_anim_run->setPosition(128+64, 128);
    player_anim_run->setWorldPos({6,4});
    player_anim_run->assignAnimation("OW_RUN");
    addEntity(player_anim_run);

    /*Animated* player_anim_spin = new Animated(&this->_data->assets, "sprites/characters/DW_HERO", 20);
    player_anim_spin->setUV(32, 0, 32, 32);
    player_anim_spin->setPosition(256, 256);
    player_anim_spin->assignAnimation("DEBUG_SPIN");
    addObject(player_anim_spin);

    Entity* big_anim = new Entity(&this->_data->assets, "sprites/characters/DW_PLAYGROUND_VAN", 4);
    big_anim->setWorldPos({20, 8});
    big_anim->setUV(64, 0, 64, 64);
    //big_anim->setPosition(256, 256);
    big_anim->setWorldSize({1, 1});
    addEntity(big_anim);

    Entity* lifejam_guy = new Entity(&this->_data->assets, "sprites/characters/lifejam_guy", 20);
    //lifejam_guy->setPosition(512, 512);
    lifejam_guy->setWorldPos({19, 17});
    lifejam_guy->setWorldSize({2, 2});
    lifejam_guy->assignAnimation("GEN_FLIP");
    addObject(lifejam_guy);*/

    /*Entity* lifejam_guy2 = new Entity(&this->_data->assets, "sprites/characters/lifejam_guy", 20, {33, 17});
    //lifejam_guy->setPosition(512, 512);
    lifejam_guy2->setWorldSize({2, 2});
    lifejam_guy2->assignAnimation("GEN_FLIP");
    addObject(lifejam_guy2);*/

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
            if (e.key.code == sf::Keyboard::Enter) {
                this->_data->states.addState(Engine::StateRef(new BattleState(this->_data)), false);
                break;
            }

            /*if (e.key.code == sf::Keyboard::Down) {
                player->move(Direction::DOWN, 200);
            } else if (e.key.code == sf::Keyboard::Up) {
                player->move(Direction::UP, 200);
            } else if (e.key.code == sf::Keyboard::Left) {
                player->move(Direction::LEFT, 200);
            } else if (e.key.code == sf::Keyboard::Right) {
                player->move(Direction::RIGHT, 200);
            }*/

            if (e.key.code == sf::Keyboard::A) {
                player->assignAnimation("OW_AUBREY_SPIN");
            }

            if (e.key.code == sf::Keyboard::Numpad2) {
                v.move(0, 32);
                this->_data->window->setView(v);
            } else if (e.key.code == sf::Keyboard::Numpad8) {
                v.move(0, -32);
                this->_data->window->setView(v);
            } else if (e.key.code == sf::Keyboard::Numpad4) {
                v.move(-32, 0);
                this->_data->window->setView(v);
            } else if (e.key.code == sf::Keyboard::Numpad6) {
                v.move(32, 0);
                this->_data->window->setView(v);
            }
                
            break;
        default:
            break;
    }
}

// marks dt to not warn compiler
void OverworldState::updateState(sf::Time deltaTime)
{
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
        player->setSprite(&this->_data->assets, "sprites/characters/DW_AUBREY_RUN");
    } else {

    }*/

    sf::View view = this->_data->window->getView();
    sf::FloatRect playerRect = player->getBounds();
    view.setCenter(playerRect.left + playerRect.width/2, playerRect.top + playerRect.height/2);
    this->_data->window->setView(view);

    //sf::Time duration = _clock.restart();
    int moveSpeed = 100; //300;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player->move(Direction::DOWN, moveSpeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player->move(Direction::UP, moveSpeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player->move(Direction::LEFT, moveSpeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player->move(Direction::RIGHT, moveSpeed);
    }

    //player->setZIndex(-player->getZIndex());

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
    // if we're repeating
    if(_repeatX || _repeatY) {
        // create a render texture to render our map to
        sf::RenderTexture extendedMapTexture;
        extendedMapTexture.create(_size.x, _size.y);
        
        // render layers to it normally (skip images, to maybe remplace with skipping repeating images)
        std::vector<Layer*>::iterator itl = mapLayers.begin();
        while (itl != mapLayers.end()) {
            this->_data->window->draw(**itl);
            if((*itl)->getType() != LayerType::Image) {
                extendedMapTexture.draw(**itl);
            }
            itl++;
        }
        std::multimap<int, Object*>::iterator itr;
        for (itr = _objects.begin(); itr != _objects.end(); ++itr) {
            /*_data->window->draw(*(itr->second));*/
            Object* obj = itr->second;
            //extendedMapTexture.draw(*(itr->second));
            extendedMapTexture.draw(*obj);
            //std::cout << obj->getBounds().left << ", " << obj->getBounds().top << std::endl;
            //if((*(itr->second)).setPosition({0,0}))
            // render the object a second time if our room is looping
            // and it's going over the edge of the screen
            //TODO top left doesn't render
            sf::Vector2i renderOffset = {0, 0};
            while(obj->getBounds().left + _size.x * renderOffset.x < 0)
                renderOffset.x++;
            while(obj->getBounds().top + _size.y * renderOffset.y < 0)
                renderOffset.y++;
            while(obj->getBounds().left + obj->getBounds().width + _size.x * renderOffset.x > _size.x)
                renderOffset.x--;
            while(obj->getBounds().top + obj->getBounds().height + _size.y * renderOffset.y > _size.y)
                renderOffset.y--;
            if(renderOffset.x || renderOffset.y) {
                obj->move({(float)_size.x * renderOffset.x, (float)_size.y * renderOffset.y});
                extendedMapTexture.draw(*(itr->second));
                obj->move({(float)_size.x * -renderOffset.x, (float)_size.y * -renderOffset.y});
            }
            /*if(obj->getZIndex() == 1)
                std::cout << renderOffset.x << ", " << renderOffset.y << std::endl;*/
            /*int offset = 0;
            while(obj->getBounds().left + _size.x * offset < 0)
                offset++;
            if(offset > 0) {
                obj->move({(float)_size.x * offset, 0});
                extendedMapTexture.draw(*(itr->second));
                obj->move({(float)-_size.x * offset, 0});
            }*/
            /*if(obj->getBounds().left < 0) {
                obj->move({(float)_size.x,0});
                extendedMapTexture.draw(*(itr->second));
                obj->move({(float)-_size.x,0});
            }
            if(obj->getBounds().top < 0) {
                obj->move({0,(float)_size.y});
                extendedMapTexture.draw(*(itr->second));
                obj->move({0,(float)-_size.y});
            }
            if(obj->getBounds().left + obj->getBounds().width > _size.x) {
                obj->move({(float)-_size.x,0});
                extendedMapTexture.draw(*(itr->second));
                obj->move({(float)_size.x,0});
            }
            if(obj->getBounds().top + obj->getBounds().height > _size.y) {
                obj->move({0,(float)-_size.y});
                extendedMapTexture.draw(*(itr->second));
                obj->move({0,(float)_size.y});
            }*/
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

bool OverworldState::isValidMove(Actor* a, Vec2i newPos) {
    std::vector<Entity*>::iterator ite = _entities.begin();
    while (ite != _entities.end()) {
        Entity* ent = (*ite);
        for(int i=0; i < ent->getWorldSize().x * ent->getWorldSize().y; i++) {
            for(int j=0; j < a->getWorldSize().x * a->getWorldSize().y; j++) {
                sf::Vector2i entPos = sf::Vector2i(ent->getWorldPos().x + i % ent->getWorldSize().y, ent->getWorldPos().y + i * ent->getWorldSize().y);
                sf::Vector2i aPos = sf::Vector2i(newPos.x + j % a->getWorldSize().y, newPos.y + j * a->getWorldSize().y);
                //std::cout << "ent(" << entPos.x << "," << entPos.y << ")" << " " << "a(" << aPos.x << "," << aPos.y << ")" << std::endl;

                if(entPos == aPos)
                    return false;
            }
        }
        ite++;
    }
    return true;
}

Entity* OverworldState::addEntity(Entity* e) {
    _entities.push_back(e);
    return (Entity*) addObject(e);
}

void OverworldState::removeEntity(Entity* e) {
    removeObject(e);
    _entities.push_back(e);
}