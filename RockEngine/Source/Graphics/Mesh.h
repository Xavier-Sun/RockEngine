#ifndef MESH_H
#define MESH_H

#include <glad\glad.h>
#include <vector>

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

class Mesh
{
private:
	unsigned int VBO;
	unsigned int EBO;

public:
	std::vector<Vertex>* vertices;
	std::vector<unsigned int>* indices;
	std::vector<Texture>* textures;
	unsigned int VAO;

	Mesh(std::vector<Vertex>* p_vertices, std::vector<unsigned int>* p_indices, std::vector<Texture>* p_textures);
	void draw(Shader* p_shader);
};

#endif