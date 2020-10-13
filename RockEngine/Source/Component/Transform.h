#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

class Transform : public Component
{
private:
    glm::mat4 model_matrix = glm::mat4(1.0f);
    
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 euler_angles = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    friend class EditorUI;

public:
    static std::vector<Transform*> collection;

    glm::mat4 get_model_matrix();

    void rotate_around(float degree, const glm::vec3& axis);
    void translate(const glm::vec3& value);
    void rescale(const glm::vec3& value);

    Transform(Entity* p_entity);
    Transform(const Transform& p_transform);
    virtual Component* get_copy() override;
    virtual ~Transform() override;
    virtual std::string get_component_type_name() override;
    virtual ComponentType get_component_type() override;
};

#endif