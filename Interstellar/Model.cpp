#include "Model.h"

void Model::render()
{
	for (int i = 0; i < this->meshes.size(); i++)
	{
		this->meshes.at(i)->render(this->shader);
	}
}