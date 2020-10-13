#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "System.h"
#include "Graphics\Shader.h"
#include "Graphics\Model.h"
#include "Component\SceneBlock.h"
#include "Component\Renderer.h"
#include "Component\EditorCamera.h"
#include "Entity\Entity.h"

class RenderSystem : public System
{
private:
	void render_on_scene_block();

public:
	virtual void init() override;
	virtual void update() override;
};

#endif