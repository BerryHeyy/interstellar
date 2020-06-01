#pragma once

#include <GL/glew.h>

#include <iostream>
#include <vector>

#include "Material.hpp"
#include "Vertex.hpp"
#include "shader.hpp"
#include "Primitive.hpp"

class Mesh
{
private:
	unsigned int nrOfVertices;
	unsigned int nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 modelMatrix;

	void initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices);

	void updateModelMatrix();
	void updateUniforms(Shader* shader);


public:
	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices, glm::vec3 position = glm::vec3(0.0f), 
		glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));

	Mesh(Primitive* primitive, glm::vec3 position = glm::vec3(0.0f),	glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));

	~Mesh();

	void update();
	void render(Shader* shader);

#pragma region Accesors

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();

#pragma endregion

#pragma region Modifiers

	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);

	void move(glm::vec3 position);
	void rotate(glm::vec3 rotation);
	void resize(glm::vec3 scale);

#pragma endregion
};
