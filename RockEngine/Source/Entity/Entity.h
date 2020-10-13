#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>

#include "Component\Component.h"
#include "Component\Transform.h"

class Entity final
{
private:
	static std::vector<Entity*> collection;
	static Entity* root_entity;

	Transform* transform;
	std::vector<Component*> components;
	std::vector<Entity*> children;
	Entity* parent;
	std::string name;
	std::string tag;

	friend class EditorUI;

public:
	static Entity* find_by_name(const std::string& p_name);
	static Entity* find_by_tag(const std::string& p_tag);

	bool active;

	Transform* get_transform();
	std::string get_name();
	void set_name(const std::string& p_name);
	Entity* get_parent();
	void set_parent(Entity* p_parent);
	Entity* find_child_by_name(const std::string& p_name);
	Entity* find_child_by_tag(const std::string& p_tag);

	template <typename T>
	T* add_component();

	template <typename T>
	void remove_component();

	template <typename T>
	T* get_component();

	Entity();
	Entity(Entity* p_parent);
	Entity(Entity* p_parent, const glm::vec3& p_position, const glm::vec3& p_scale);
	Entity(const glm::vec3& p_position, const glm::vec3& p_scale);
	Entity(const Entity& p_entity);
	~Entity();
};

template<typename T>
inline T* Entity::add_component()
{
	for (auto component : components)
	{
		if (dynamic_cast<T*>(component))
		{
			return nullptr;
		}
	}

	T* component = new T(this);
	components.push_back(component);
	if (typeid(Transform) == typeid(T))
	{
		transform = (Transform*)component;
	}

	return component;
}

template<typename T>
inline void Entity::remove_component()
{
	if (typeid(T) != typeid(Transform))
	{
		for (auto i = components.begin(); i != components.end(); i++)
		{
			if (dynamic_cast<T*>(*i))
			{
				components.erase(i);
				delete* i;
				return;
			}
		}
	}
}

template<typename T>
inline T* Entity::get_component()
{
	for (auto i : components)
	{
		if (dynamic_cast<T*>(i))
		{
			return (T*)i;
		}
	}

	return nullptr;
}

#endif