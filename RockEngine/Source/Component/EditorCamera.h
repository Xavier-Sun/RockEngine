#ifndef EDITOR_CAMERA_H
#define EDITOR_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class EditorCamera : Component
{
private:
    static void update_data();

    EditorCamera() : Component(nullptr) {}

public:
    static glm::vec3 position;
    static glm::vec3 front;
    static glm::vec3 up;
    static glm::vec3 right;
    static glm::vec3 world_up;
    static float yaw;
    static float pitch;
    static float movement_speed;
    static float mouse_sensitivity;
    static float zoom;

    static glm::mat4 projection;
    static glm::mat4 view;

    static void process_keyboard(CameraMovement p_direction, float p_delta_time);
    static void process_mouse_movement(float offset_x, float offset_y);
    static void process_mouse_scroll(float offset_y);

    virtual ~EditorCamera() override {}
    EditorCamera(const EditorCamera&) = delete;
    EditorCamera& operator=(const EditorCamera&) = delete;
};

#endif