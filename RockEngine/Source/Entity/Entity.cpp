#include "Entity.h"

std::vector<Entity*> Entity::collection;
Entity* Entity::root_entity = new Entity(nullptr);

Entity* Entity::find_by_name(const std::string& p_name)
{
	for (auto i : collection)
	{
		if (i->name == p_name)
		{
			return i;
		}
	}

	return nullptr;
}

Entity* Entity::find_by_tag(const std::string& p_tag)
{
	for (auto i : collection)
	{
		if (i->tag == p_tag)
		{
			return i;
		}
	}

	return nullptr;
}

Transform* Entity::get_transform()
{
	return transform;
}

std::string Entity::get_name()
{
	return name;
}

void Entity::set_name(const std::string& p_name)
{
	name = p_name;
}

Entity* Entity::get_parent()
{
	return parent;
}

void Entity::set_parent(Entity* p_parent)
{
	parent = p_parent;
}

Entity* Entity::find_child_by_name(const std::string& p_name)
{
	for (auto i : children)
	{
		if (i->name == p_name)
		{
			return i;
		}
	}

	return nullptr;
}

Entity* Entity::find_child_by_tag(const std::string& p_tag)
{
	for (auto i : children)
	{
		if (i->tag == p_tag)
		{
			return i;
		}
	}

	return nullptr;
}

Entity::Entity() : Entity(root_entity)
{

}

Entity::Entity(Entity* p_parent)
{
	parent = p_parent;
	active = true;
	name = "Unnamed Entity";
	tag = "Untagged";
	Transform* new_transform = new Transform(this);
	transform = new_transform;
	components.push_back(new_transform);
	collection.push_back(this);
	if (p_parent != nullptr)
	{
		parent->children.push_back(this);
	}
}

Entity::Entity(Entity* p_parent, const glm::vec3& p_position, const glm::vec3& p_scale) : Entity(p_parent)
{
	transform->translate(p_position);
	transform->rescale(p_scale);
}

Entity::Entity(const glm::vec3& p_position, const glm::vec3& p_scale) : Entity(root_entity, p_position, p_scale)
{

}

Entity::Entity(const Entity& p_entity)
{
	for (auto component : p_entity.components)
	{
		components.push_back(component->get_copy());
	}
	transform = get_component<Transform>();
	parent = p_entity.parent;
	if (parent != nullptr)
	{
		parent->children.push_back(this);
	}
	name = p_entity.name;
	tag = p_entity.tag;
	children.clear();
}

Entity::~Entity()
{
	for (auto component : components)
	{
		delete component;
	}

	for (auto i = collection.begin(); i != collection.end(); i++)
	{
		if (*i == this)
		{
			collection.erase(i);
			break;
		}
	}
}
