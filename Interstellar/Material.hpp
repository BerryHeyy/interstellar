#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "shader.hpp"

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

public:
	Material(glm::vec3 ambient,	glm::vec3 diffuse, glm::vec3 specular)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}

	~Material() {}

	void sendToShader(Shader& shaderProgram)
	{
		shaderProgram.setVec3("material.ambient", this->ambient);
		shaderProgram.setVec3("material.diffuse", this->diffuse);
		shaderProgram.setVec3("material.specular", this->specular);
	}
};