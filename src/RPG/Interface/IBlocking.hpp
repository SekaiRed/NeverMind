#pragma once
#ifndef IBLOCKING_INTERFACE
#define IBLOCKING_INTERFACE

#include <array>
#include "../../Engine/Vec2i.hpp"
#include "../Objects/Actor.hpp"

class Actor;

class IBlocking {
public:
	virtual bool isValidMove(Actor* a, Vec2i newPos) {
		return true;
	};
};

#endif