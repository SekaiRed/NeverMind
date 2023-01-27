#include "Direction.hpp"

Direction::Direction(Vec2i vec) {
    this->vec = vec;
};

Vec2i Direction::getVector() {
    return vec;
}

const Direction Direction::LEFT = Vec2i(-1, 0);
const Direction Direction::UP = Vec2i(0, -1);
const Direction Direction::RIGHT = Vec2i(1, 0);
const Direction Direction::DOWN = Vec2i(0, 1);

Direction::Direction() {
    this->vec = Direction::DOWN.vec; 
}

const std::array<Direction, 4> Direction::values = {
    LEFT,
    UP,
    RIGHT,
    DOWN
};

/*Direction& Direction::operator++() {
    
    return values.at(?);
}*/
bool Direction::operator==(const Direction &d) const {
    return (vec == d.vec);
}