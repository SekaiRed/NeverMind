#include "MapLayer.hpp"

/*Ok so either I store the actors per layer and then use them to rneder on the right one or everything is in the overworldstate
Oooooooooor I can just make it so actors are never deleted, which might be weird idk*/

MapLayer::MapLayer(const tmx::Map& map, std::size_t idx) : Layer::Layer(map, idx) {
    const auto& layers = map.getLayers();
    if (map.getOrientation() == tmx::Orientation::Orthogonal &&
        idx < layers.size() && layers[idx]->getType() == tmx::Layer::Type::Tile)
    {
        //round the chunk size to the nearest tile
        const auto tileSize = map.getTileSize();
        m_chunkSize.x = std::floor(m_chunkSize.x / tileSize.x) * tileSize.x;
        m_chunkSize.y = std::floor(m_chunkSize.y / tileSize.y) * tileSize.y;
        m_MapTileSize.x = map.getTileSize().x;
        m_MapTileSize.y = map.getTileSize().y;
        const auto& layer = layers[idx]->getLayerAs<tmx::TileLayer>();
        createChunks(map, layer);

        auto mapSize = map.getBounds();
        m_globalBounds.width = mapSize.width;
        m_globalBounds.height = mapSize.height;
    }
    else
    {
        std::cout << "Not a valid orthogonal layer, nothing will be drawn." << std::endl;
    }
}

void MapLayer::setTile(int tileX, int tileY, tmx::TileLayer::Tile tile, bool refresh) {
    sf::Vector2u chunkLocale;
    const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
    selectedChunk->setTile(chunkLocale.x, chunkLocale.y, tile, refresh);
}
tmx::TileLayer::Tile MapLayer::getTile(int tileX, int tileY) {
    sf::Vector2u chunkLocale;
    const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
    return selectedChunk->getTile(chunkLocale.x, chunkLocale.y);
}

void MapLayer::setColor(int tileX, int tileY, sf::Color color, bool refresh) {
    sf::Vector2u chunkLocale;
    const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
    selectedChunk->setColor(chunkLocale.x, chunkLocale.y, color, refresh);
}
sf::Color MapLayer::getColor(int tileX, int tileY) {
    sf::Vector2u chunkLocale;
    const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
    return selectedChunk->getColor(chunkLocale.x, chunkLocale.y);
}

void MapLayer::update(sf::Time elapsed) {
    for (auto& c : m_visibleChunks) {
        for (AnimationState& as : c->getActiveAnimations()) {
            as.currentTime += elapsed;

            tmx::TileLayer::Tile tile;
            std::uint32_t animTime = 0;
            auto x = as.animTile.animation.frames.begin();
            while (animTime < as.currentTime.asMilliseconds()) {
                if (x == as.animTile.animation.frames.end()) {
                    x = as.animTile.animation.frames.begin();
                    as.currentTime -= sf::milliseconds(animTime);
                    animTime = 0;
                }

                tile.ID = x->tileID;
                animTime += x->duration;
                x++;
            }

            setTile(as.tileCords.x, as.tileCords.y, tile);
        }
    }
}