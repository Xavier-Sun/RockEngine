#ifndef RENDERER_H
#define RENDERER_H

#include "Component.h"

class Model;
class Shader;

class Renderer : public Component
{
public:
	static std::vector<Renderer*> collection;
	Model* model;
	Shader* shader;

	Renderer(Entity* p_entity);
	Renderer(const Renderer& p_renderer);
	virtual ~Renderer() override;
	virtual Component* get_copy() override;
	virtual std::string get_component_type_name() override;
	virtual ComponentType get_component_type() override;
};

#endif