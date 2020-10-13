#include "EditorCameraSystem.h"

void EditorCameraSystem::update()
{
	if (Input::get_key(KeyCode::A))
	{
		EditorCamera::process_keyboard(CameraMovement::LEFT, Time::get_delta_time());
	}
	if (Input::get_key(KeyCode::W))
	{
		EditorCamera::process_keyboard(CameraMovement::FORWARD, Time::get_delta_time());
	}
	if (Input::get_key(KeyCode::S))
	{
		EditorCamera::process_keyboard(CameraMovement::BACKWARD, Time::get_delta_time());
	}
	if (Input::get_key(KeyCode::D))
	{
		EditorCamera::process_keyboard(CameraMovement::RIGHT, Time::get_delta_time());
	}

	if (Input::get_button(1))
	{
		EditorCamera::process_mouse_movement(Input::get_axis(InputAxis::MOUSE_X), -Input::get_axis(InputAxis::MOUSE_Y));
	}

	EditorCamera::process_mouse_scroll(Input::get_axis(InputAxis::SCROLL_Y));

	EditorCamera::projection = glm::perspective(glm::radians(EditorCamera::zoom), (float)16 / 9, 0.1f, 100.0f);
	EditorCamera::view = glm::lookAt(EditorCamera::position, EditorCamera::position + EditorCamera::front, EditorCamera::up);
}
