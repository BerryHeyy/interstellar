#pragma once

#include "CelestialObject.hpp"
#include "System.hpp"
#include "Position.hpp"

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

