#pragma once

#include <GL/glew.h>
#include <vector>

#include "Vertex.h"

class Primitive
{
private:

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:

	Primitive();
	virtual ~Primitive();

	void set(const Vertex* vertices, const unsigned int nrOfVertices, const GLuint* indices, const unsigned int nrOfIndices);

	Vertex* getVertices();
	GLuint* getIndices();
	const unsigned int getNrOfVertices();
	const unsigned int getNrOfIndices();

};