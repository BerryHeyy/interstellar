#include "Mesh.h"

Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices, glm::vec3 position,
	glm::vec3 rotation, glm::vec3 scale)
{
	this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndices);

	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

}

Mesh::Mesh(Primitive* primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->initVAO(primitive->getVertices(), primitive->getNrOfVertices(), primitive->getIndices(), primitive->getNrOfIndices());

	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);

}

void Mesh::initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
{
	// Set var
	this->nrOfVertices = nrOfVertices;
	this->nrOfIndices = nrOfIndices;


	// Create VAO
	glCreateVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

	// Vertex Attribute Pointers (input assembly)
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Mesh::updateModelMatrix()
{
	this->modelMatrix = glm::mat4(1.0f);

	this->modelMatrix = glm::translate(this->modelMatrix, this->position);
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
}

void Mesh::updateUniforms(Shader* shader)
{
	shader->setMat4("model", this->modelMatrix);
}

void Mesh::update()
{

}

void Mesh::render(Shader* shader)
{
	// Update uniforms
	this->updateModelMatrix();
	this->updateUniforms(shader);
	shader->use();

	// Bind VAO
	glBindVertexArray(this->VAO);
	// Render
	glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
}

#pragma region Accessors

glm::vec3 Mesh::getPosition()
{
	return this->position;
}

glm::vec3 Mesh::getRotation()
{
	return this->rotation;
}

glm::vec3 Mesh::getScale()
{
	return this->scale;
}

#pragma endregion

#pragma region Modifiers

void Mesh::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Mesh::setRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Mesh::setScale(glm::vec3 scale)
{
	this->scale = scale;
}


void Mesh::move(glm::vec3 position)
{
	this->position += position;
}

void Mesh::rotate(glm::vec3 rotation)
{
	this->rotation += rotation;
}

void Mesh::resize(glm::vec3 scale)
{
	this->scale += scale;
}

#pragma endregion