#include "Renderer.h"

std::vector<Renderer*> Renderer::collection;

Renderer::Renderer(Entity* p_entity) : Component(p_entity)
{
	model = nullptr;
	shader = nullptr;
	collection.push_back(this);
}

Renderer::Renderer(const Renderer& p_renderer) : Component(p_renderer.entity)
{
	model = p_renderer.model;
	shader = p_renderer.shader;
	collection.push_back(this);
}

Renderer::~Renderer()
{
	for (auto i = collection.begin(); i != collection.end(); i++)
	{
		if (*i == this)
		{
			collection.erase(i);
			return;
		}
	}
}

Component* Renderer::get_copy()
{
	return new Renderer(*this);
}

std::string Renderer::get_component_type_name()
{
	return "Renderer";
}

ComponentType Renderer::get_component_type()
{
	return ComponentType::RENDERER;
}
