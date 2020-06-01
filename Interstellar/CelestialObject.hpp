#pragma once

#include "System.hpp"
#include "Position.hpp"

class CelestialObject
{
private:
	System system;

	Position position;

public:
	CelestialObject(System system, Position position);

};

