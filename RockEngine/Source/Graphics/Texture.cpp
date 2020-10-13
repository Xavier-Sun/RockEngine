#include "Texture.h"

Texture::Texture(const std::string& file_path, const std::string& p_name, TextureType p_type)
{
    name = p_name;
    type = p_type;

    glGenTextures(1, &id);

    int channel_num;
    unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &channel_num, 0);
    if (data)
    {
        GLenum format = GL_RGB;

        switch (channel_num)
        {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            break;
        }

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load texture, file path:\n" << file_path << std::endl;
    }

    stbi_image_free(data);
}
