#pragma once

#include <vector>

#include "Mesh.h"
#include "shader.h"

class Model
{
private:

	Material* material;
	Shader* shader;

	glm::vec3 position;
	std::vector<Mesh*> meshes;

public:

	void render();


};

