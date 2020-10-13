#include "Component.h"

Component::Component(Entity* p_entity)
{
    entity = p_entity;
}

Component* Component::get_copy()
{
    return nullptr;
}

std::string Component::get_component_type_name()
{
    return "Component";
}

ComponentType Component::get_component_type()
{
    return ComponentType::NONEXISTENT;
}
