#include "CelestialObject.hpp"

CelestialObject::CelestialObject(System system, Position position)
{
	this->system = system;
	this->position = position;
}