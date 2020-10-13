#include "Transform.h"

std::vector<Transform*> Transform::collection;

glm::mat4 Transform::get_model_matrix()
{
	return model_matrix;
}

void Transform::rotate_around(float degree, const glm::vec3& axis)
{
	model_matrix = glm::rotate(model_matrix, degree, axis);

	euler_angles = axis;
}

void Transform::translate(const glm::vec3& value)
{
	model_matrix = glm::translate(model_matrix, value);

	position = value;
}

void Transform::rescale(const glm::vec3& value)
{
	model_matrix = glm::scale(model_matrix, value);

	scale = value;
}

Transform::Transform(Entity* p_entity) : Component(p_entity)
{
	collection.push_back(this);
}

Transform::Transform(const Transform& p_transform) : Component(p_transform.entity)
{
	model_matrix = p_transform.model_matrix;
	position = p_transform.position;
	euler_angles = p_transform.euler_angles;
	scale = p_transform.scale;
}

Component* Transform::get_copy()
{
	return new Transform(*this);
}

Transform::~Transform()
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

std::string Transform::get_component_type_name()
{
	return "Transform";
}

ComponentType Transform::get_component_type()
{
	return ComponentType::TRANSFORM;
}
