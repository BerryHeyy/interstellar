#pragma once

#include "CelestialObject.h"
#include "System.h"
#include "Position.h"

enum PlanetType
{
	ROCKY,
	ICY,
	GAS,
	EARTH_LIKE
};

class Planet : CelestialObject
{
private:
	PlanetType planetType;
	int diameter;

public:
	Planet(System system, Position position);

};

