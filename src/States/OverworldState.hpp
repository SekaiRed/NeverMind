#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "../Game.hpp"
#include "State.hpp"
#include "../Graphics/Overworld/MapLayer.hpp"

class OverworldState : public Engine::State
{
public:
	OverworldState(std::string filename, GameDataRef data);
	//~MainMenuState() = default;

	void initState();
	void updateEvents(sf::Event e);
	void updateState(float dt __attribute__((unused)));
	void drawState(float dt __attribute__((unused)));

private:
	GameDataRef _data;
    //std::vector<MapLayer> mapLayers;
};