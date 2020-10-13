#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <iostream>

#include "Texture.h"
#include "Mesh.h"

class Model
{
public:
	static std::vector<Model*> collection;
	static void destroy(const std::string& p_name);
	static Model* get_model(const std::string& p_name);

	std::vector<Texture*> loaded_textures;
	std::vector<Mesh> meshes;
	std::string directory;
	std::string name;

	Model(const std::string& p_name, const std::string& p_path);
	~Model() = default;
	void draw(Shader* shader);
	void process_node(aiNode* node, const aiScene* scene);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> load_texture(aiMaterial* aimaterial, aiTextureType aitexture_type, TextureType type);
};

#endif