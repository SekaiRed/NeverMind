#pragma once

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "../../Game.hpp"
#include "BattleState.hpp"
#include "../../Engine/States/BaseState.hpp"
#include "../../Graphics/Overworld/MapLayer.hpp"
#include "../../Graphics/Overworld/ImageLayer.hpp"
#include "../Objects/Actor.hpp"

class OverworldState : public BaseState, public IBlocking
{
public:
	OverworldState(std::string filename, GameDataRef data);
	
	void drawWorld(int offsetX, int offsetY, bool ignoreImages = false);
	Entity* addEntity(Entity* e);
	void removeEntity(Entity* e);

	//Overrides
	void initState();
	void updateEvents(sf::Event e);
	void updateState(sf::Time deltaTime);
	void drawState(sf::Time deltaTime);
	bool isValidMove(Actor* a, Vec2i newPos);

private:
	//GameDataRef _data;
	sf::Color _color;
    std::vector<Layer*> mapLayers;
	std::vector<Entity*> _entities;
    /*std::vector<Entity*> _addingEntitiesQueue;
    std::vector<Entity*> _deleteEntitiesQueue;*/
	sf::Vector2i _size;
	bool _repeatX = false;
	bool _repeatY = false;
	//Graphic* player;
	Actor* player;
};