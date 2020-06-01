#pragma once

#include <vector>

#include "Mesh.hpp"
#include "shader.hpp"

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

