#include "Primitives.hpp"

namespace primitive
{
	Quad::Quad() : Primitive()
	{
		// Create quad data
		Vertex vertices[] = {
			// Position							Color								Normals
			glm::vec3(-0.5f,  0.5f, 0.0f),		glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f,  0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f)

		};

		unsigned int nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		unsigned int nrOfIndices = sizeof(indices) / sizeof(unsigned int);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}

	Triangle::Triangle() : Primitive()
	{
		// Create quad data
		Vertex vertices[] = {
			// Position							Color								Normals
			glm::vec3(0.0f, 0.5f, 0.0f),		glm::vec3(1.0f, 0.0f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),		glm::vec3(0.0f, 0.0f, 0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),
		};

		unsigned int nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		unsigned int indices[] = {
			0, 1, 2
		};

		unsigned int nrOfIndices = sizeof(indices) / sizeof(unsigned int);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
}