#pragma once

#include "Layer.hpp"

class ImageLayer final : public Layer {
public:
    ImageLayer(const tmx::Map& map, std::size_t idx);

    virtual LayerType getType() const;
};