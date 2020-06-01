#pragma once

#include "System.h"
#include "Position.h"

class CelestialObject
{
private:
	System system;

	Position position;

public:
	CelestialObject(System system, Position position);

};

