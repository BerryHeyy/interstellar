#include "Primitive.hpp"

Primitive::Primitive()
{

}

Primitive::~Primitive()
{

}

void Primitive::set(const Vertex* vertices, const unsigned int nrOfVertices, const GLuint* indices, const unsigned int nrOfIndices)
{

	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}

	for (size_t i = 0; i < nrOfIndices; i++)
	{
		this->indices.push_back(indices[i]);
	}

}

Vertex* Primitive::getVertices()
{
	return this->vertices.data();
}

GLuint* Primitive::getIndices()
{
	return this->indices.data();
}

const unsigned int Primitive::getNrOfVertices()
{
	return this->vertices.size();
}

const unsigned int Primitive::getNrOfIndices()
{
	return this->indices.size();
}