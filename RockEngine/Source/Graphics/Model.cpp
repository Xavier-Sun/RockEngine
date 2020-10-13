#include "Model.h"

std::vector<Model*> Model::collection;

void Model::destroy(const std::string& p_name)
{
    auto i = get_model(p_name);
    if (i != nullptr)
    {
        delete i;
    }
}

Model* Model::get_model(const std::string& p_name)
{
    for (auto model : collection)
    {
        if (model->name == p_name)
        {
            return model;
        }
    }

    return nullptr;
}

Model::Model(const std::string& p_name, const std::string& p_path)
{
    Assimp::Importer importer;
    const aiScene* aiscene = importer.ReadFile(p_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!aiscene || aiscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiscene->mRootNode)
    {
        std::cout << "ASSIMP Error:\n" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = p_path.substr(0, p_path.find_last_of('/'));
    process_node(aiscene->mRootNode, aiscene);

    destroy(p_name);
    name = p_name;
    collection.push_back(this);
}

void Model::draw(Shader* shader)
{
    for (auto& mesh : meshes)
    {
        mesh.draw(shader);
    }
}

void Model::process_node(aiNode* ainode, const aiScene* aiscene)
{
    for (unsigned int i = 0; i < ainode->mNumMeshes; i++)
    {
        aiMesh* mesh = aiscene->mMeshes[ainode->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, aiscene));
    }
    for (unsigned int i = 0; i < ainode->mNumChildren; i++)
    {
        process_node(ainode->mChildren[i], aiscene);
    }
}

Mesh Model::process_mesh(aiMesh* aimesh, const aiScene* aiscene)
{
    std::vector<Vertex>* vertices = new std::vector<Vertex>();
    std::vector<unsigned int>* indices = new std::vector<unsigned int>();
    std::vector<Texture>* textures = new std::vector<Texture>();

    for (unsigned int i = 0; i < aimesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 temp_vec3;
        glm::vec2 temp_vec2;

        temp_vec3.x = aimesh->mVertices[i].x;
        temp_vec3.y = aimesh->mVertices[i].y;
        temp_vec3.z = aimesh->mVertices[i].z;
        vertex.position = temp_vec3;

        if (aimesh->HasNormals())
        {
            temp_vec3.x = aimesh->mNormals[i].x;
            temp_vec3.y = aimesh->mNormals[i].y;
            temp_vec3.z = aimesh->mNormals[i].z;
            vertex.normal = temp_vec3;
        }

        if (aimesh->mTextureCoords[0])
        {
            temp_vec2.x = aimesh->mTextureCoords[0][i].x;
            temp_vec2.y = aimesh->mTextureCoords[0][i].y;
            vertex.texture_coordinates = temp_vec2;
        }
        else
        {
            vertex.texture_coordinates = glm::vec2(0.0f, 0.0f);
        }

        vertices->push_back(vertex);
    }

    for (unsigned int i = 0; i < aimesh->mNumFaces; i++)
    {
        aiFace aiface = aimesh->mFaces[i];
        for (unsigned int j = 0; j < aiface.mNumIndices; j++)
        {
            indices->push_back(aiface.mIndices[j]);
        }
    }

    aiMaterial* aimaterial = aiscene->mMaterials[aimesh->mMaterialIndex];

    std::vector<Texture> diffuse_maps = load_texture(aimaterial, aiTextureType_DIFFUSE, TextureType::TEXTURE_DIFFUSE);
    textures->insert(textures->end(), diffuse_maps.begin(), diffuse_maps.end());

    std::vector<Texture> specular_maps = load_texture(aimaterial, aiTextureType_SPECULAR, TextureType::TEXTURE_SPECULAR);
    textures->insert(textures->end(), specular_maps.begin(), specular_maps.end());

    std::vector<Texture> normal_maps = load_texture(aimaterial, aiTextureType_HEIGHT, TextureType::TEXTURE_NORMAL);
    textures->insert(textures->end(), normal_maps.begin(), normal_maps.end());

    std::vector<Texture> height_maps = load_texture(aimaterial, aiTextureType_AMBIENT, TextureType::TEXTURE_HEIGHT);
    textures->insert(textures->end(), height_maps.begin(), height_maps.end());

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::load_texture(aiMaterial* aimaterial, aiTextureType aitexture_type, TextureType type)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < aimaterial->GetTextureCount(aitexture_type); i++)
    {
        aiString texture_name;
        aimaterial->GetTexture(aitexture_type, i, &texture_name);
        bool loaded = false;
        for (auto j : loaded_textures)
        {
            if (j->name == texture_name.C_Str())
            {
                textures.push_back(*j);
                loaded = true;
                break;
            }
        }

        if (!loaded)
        {
            Texture texture(directory + '/' + texture_name.C_Str(), texture_name.C_Str(), type);
            textures.push_back(texture);
            loaded_textures.push_back(&texture);
        }
    }

    return textures;
}
