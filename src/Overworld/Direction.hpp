#pragma once

#include <array>
#include "../Engine/Vec2i.hpp"

class Direction {
private:
	Vec2i vec;
	Direction(Vec2i vec);
	
public:
	const static Direction LEFT;
    const static Direction UP;
    const static Direction RIGHT;
    const static Direction DOWN;
	const static std::array<Direction, 4> values;
	Vec2i getVector();
};
