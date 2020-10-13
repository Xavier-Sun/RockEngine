#include "InputSystem.h"

void scroll_callback(GLFWwindow* window, double offset_x, double offset_y)
{
	Input::cursor_scroll_x = offset_x;
	Input::cursor_scroll_y = offset_y;
}

void InputSystem::init()
{
	glfwSetScrollCallback(Window::get_window(), scroll_callback);
}

void InputSystem::update()
{
	Input::last_cursor_x = Input::cursor_x;
	Input::last_cursor_y = Input::cursor_y;
	glfwGetCursorPos(Window::get_window(), &Input::cursor_x, &Input::cursor_y);
}
