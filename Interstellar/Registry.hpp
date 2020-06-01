#pragma once

#include <list>

#include "Registerable.hpp"

class Registry
{
private:

	std::list<Registerable> registeredObjects;

public:

	virtual void registerObject(Registerable object) = 0;

};
