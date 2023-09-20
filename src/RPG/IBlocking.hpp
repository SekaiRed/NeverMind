#pragma once

#include <array>
#include "../Engine/Vec2i.hpp"

class IBlocking {
public:
	virtual bool isValidMove(Vec2i newPos, Vec2i oldPos);
};
