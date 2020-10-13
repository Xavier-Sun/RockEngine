#include "RenderSystem.h"

void RenderSystem::render_on_scene_block()
{
	glBindFramebuffer(GL_FRAMEBUFFER, SceneBlock::FBO);

	glClearColor(SceneBlock::background_color.r, SceneBlock::background_color.g, SceneBlock::background_color.b, SceneBlock::background_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto renderer : Renderer::collection)
	{
		if (renderer->entity->active && renderer->shader && renderer->model)
		{
			renderer->shader->use();
			renderer->shader->set_mat4("projection", EditorCamera::projection);
			renderer->shader->set_mat4("view", EditorCamera::view);
			renderer->shader->set_mat4("model", renderer->entity->get_transform()->get_model_matrix());
			renderer->model->draw(renderer->shader);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderSystem::init()
{
	glGenFramebuffers(1, &SceneBlock::FBO);
	glGenTextures(1, &SceneBlock::texture);
	glGenRenderbuffers(1, &SceneBlock::RBO);
	
	glBindFramebuffer(GL_FRAMEBUFFER, SceneBlock::FBO);
	glBindTexture(GL_TEXTURE_2D, SceneBlock::texture);
	glBindRenderbuffer(GL_RENDERBUFFER, SceneBlock::RBO);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneBlock::width, SceneBlock::height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SceneBlock::width, SceneBlock::height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, SceneBlock::texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, SceneBlock::RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer is not complete." << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderSystem::update()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render_on_scene_block();
}
