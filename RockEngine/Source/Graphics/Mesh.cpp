#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>* p_vertices, std::vector<unsigned int>* p_indices, std::vector<Texture>* p_textures)
{
	vertices = p_vertices;
	indices = p_indices;
	textures = p_textures;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), &(*vertices)[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), &(*indices)[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coordinates));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw(Shader* p_shader)
{
    unsigned int diffuse_count = 1;
    unsigned int specular_count = 1;
    unsigned int normal_count = 1;
    unsigned int height_count = 1;
    for (unsigned int i = 0; i < textures->size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        switch ((*textures)[i].type)
        {
        case TextureType::TEXTURE_DIFFUSE:
            p_shader->set_int("texture_diffuse" + diffuse_count, i);
            diffuse_count++;
            break;
        case TextureType::TEXTURE_SPECULAR:
            p_shader->set_int("texture_specular" + specular_count, i);
            specular_count++;
            break;
        case TextureType::TEXTURE_NORMAL:
            p_shader->set_int("texture_normal" + normal_count, i);
            normal_count++;
            break;
        case TextureType::TEXTURE_HEIGHT:
            p_shader->set_int("texture_height" + height_count, i);
            height_count++;
            break;
        default:
            break;
        }

        glBindTexture(GL_TEXTURE_2D, (*textures)[i].id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
