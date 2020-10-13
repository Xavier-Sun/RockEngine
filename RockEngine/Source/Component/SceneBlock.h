#ifndef SCENE_BLOCK_H
#define SCENE_BLOCK_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Component\Component.h"

class SceneBlock : public Component
{
private:
	static unsigned int FBO;
	static unsigned int RBO;
	static unsigned int texture;

	SceneBlock() : Component(nullptr) {}

	friend class RenderSystem;

public:
	static const int width = 800;
	static const int height = 600;
	static glm::vec4 background_color;

	static unsigned int get_FBO() { return FBO; }
	static unsigned int get_RBO() { return RBO; }
	static unsigned int get_texture() { return texture; }
	
	virtual ~SceneBlock() override {}
	SceneBlock(const SceneBlock&) = delete;
	SceneBlock& operator=(const SceneBlock&) = delete;
};

#endif