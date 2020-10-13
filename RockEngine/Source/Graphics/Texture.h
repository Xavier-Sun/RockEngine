#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad\glad.h>
#include <stb_image.h>

#include <string>
#include <iostream>

enum class TextureType
{
	TEXTURE_DIFFUSE,
	TEXTURE_SPECULAR,
	TEXTURE_NORMAL,
	TEXTURE_HEIGHT
};

class Texture
{
public:
	unsigned int id;
	std::string name;
	TextureType type;

	int width;
	int height;

	Texture(const std::string& file_path, const std::string& p_name, TextureType p_type);
};

#endif