#include "EditorCamera.h"

glm::vec3 EditorCamera::position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 EditorCamera::front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 EditorCamera::up = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 EditorCamera::right = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 EditorCamera::world_up = glm::vec3(0.0f, 1.0f, 0.0f);
float EditorCamera::yaw = -90.0f;
float EditorCamera::pitch = 0.0f;
float EditorCamera::movement_speed = 2.5f;
float EditorCamera::mouse_sensitivity = 0.1f;
float EditorCamera::zoom = 45.0f;
glm::mat4 EditorCamera::projection;
glm::mat4 EditorCamera::view;

void EditorCamera::process_keyboard(CameraMovement p_direction, float p_delta_time)
{
    switch (p_direction)
    {
    case CameraMovement::FORWARD:
        position += front * movement_speed * p_delta_time;
        break;
    case CameraMovement::BACKWARD:
        position -= front * movement_speed * p_delta_time;
        break;
    case CameraMovement::LEFT:
        position -= right * movement_speed * p_delta_time;
        break;
    case CameraMovement::RIGHT:
        position += right * movement_speed * p_delta_time;
        break;
    default:
        break;
    }
}

void EditorCamera::process_mouse_movement(float offset_x, float offset_y)
{
    yaw += offset_x * mouse_sensitivity;
    pitch += offset_y * mouse_sensitivity;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    update_data();
}

void EditorCamera::process_mouse_scroll(float offset_y)
{
    zoom -= offset_y / 10;

    if (zoom < 1.0f)
    {
        zoom = 1.0f;
    }
    else if (zoom > 45.0f)
    {
        zoom = 45.0f;
    }
}

void EditorCamera::update_data()
{
    glm::vec3 temp
    {
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    };
    front = glm::normalize(temp);
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}
