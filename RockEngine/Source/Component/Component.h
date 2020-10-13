#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <string>

class Entity;

enum class ComponentType
{
	TRANSFORM,
	RENDERER,
	NONEXISTENT
};

class Component
{
public:
	Entity* entity;

	Component(Entity* p_entity);
	virtual ~Component() = default;
	virtual Component* get_copy();
	virtual std::string get_component_type_name();
	virtual ComponentType get_component_type();
};

#endif