#include "Input.h"

double Input::last_cursor_x = 0;
double Input::last_cursor_y = 0;
double Input::cursor_x = 0;
double Input::cursor_y = 0;
double Input::cursor_scroll_x = 0;
double Input::cursor_scroll_y = 0;

bool Input::get_key(KeyCode p_key_code)
{
	switch (p_key_code)
	{
	case KeyCode::A:
		return glfwGetKey(Window::get_window(), GLFW_KEY_A) == GLFW_PRESS;
		break;
	case KeyCode::B:
		return glfwGetKey(Window::get_window(), GLFW_KEY_B) == GLFW_PRESS;
		break;
	case KeyCode::C:
		return glfwGetKey(Window::get_window(), GLFW_KEY_C) == GLFW_PRESS;
		break;
	case KeyCode::D:
		return glfwGetKey(Window::get_window(), GLFW_KEY_D) == GLFW_PRESS;
		break;
	case KeyCode::E:
		return glfwGetKey(Window::get_window(), GLFW_KEY_E) == GLFW_PRESS;
		break;
	case KeyCode::F:
		return glfwGetKey(Window::get_window(), GLFW_KEY_F) == GLFW_PRESS;
		break;
	case KeyCode::G:
		return glfwGetKey(Window::get_window(), GLFW_KEY_G) == GLFW_PRESS;
		break;
	case KeyCode::H:
		return glfwGetKey(Window::get_window(), GLFW_KEY_H) == GLFW_PRESS;
		break;
	case KeyCode::I:
		return glfwGetKey(Window::get_window(), GLFW_KEY_I) == GLFW_PRESS;
		break;
	case KeyCode::J:
		return glfwGetKey(Window::get_window(), GLFW_KEY_J) == GLFW_PRESS;
		break;
	case KeyCode::K:
		return glfwGetKey(Window::get_window(), GLFW_KEY_K) == GLFW_PRESS;
		break;
	case KeyCode::L:
		return glfwGetKey(Window::get_window(), GLFW_KEY_L) == GLFW_PRESS;
		break;
	case KeyCode::M:
		return glfwGetKey(Window::get_window(), GLFW_KEY_M) == GLFW_PRESS;
		break;
	case KeyCode::N:
		return glfwGetKey(Window::get_window(), GLFW_KEY_N) == GLFW_PRESS;
		break;
	case KeyCode::O:
		return glfwGetKey(Window::get_window(), GLFW_KEY_O) == GLFW_PRESS;
		break;
	case KeyCode::P:
		return glfwGetKey(Window::get_window(), GLFW_KEY_P) == GLFW_PRESS;
		break;
	case KeyCode::Q:
		return glfwGetKey(Window::get_window(), GLFW_KEY_Q) == GLFW_PRESS;
		break;
	case KeyCode::R:
		return glfwGetKey(Window::get_window(), GLFW_KEY_R) == GLFW_PRESS;
		break;
	case KeyCode::S:
		return glfwGetKey(Window::get_window(), GLFW_KEY_S) == GLFW_PRESS;
		break;
	case KeyCode::T:
		return glfwGetKey(Window::get_window(), GLFW_KEY_T) == GLFW_PRESS;
		break;
	case KeyCode::U:
		return glfwGetKey(Window::get_window(), GLFW_KEY_U) == GLFW_PRESS;
		break;
	case KeyCode::V:
		return glfwGetKey(Window::get_window(), GLFW_KEY_V) == GLFW_PRESS;
		break;
	case KeyCode::W:
		return glfwGetKey(Window::get_window(), GLFW_KEY_W) == GLFW_PRESS;
		break;
	case KeyCode::X:
		return glfwGetKey(Window::get_window(), GLFW_KEY_X) == GLFW_PRESS;
		break;
	case KeyCode::Y:
		return glfwGetKey(Window::get_window(), GLFW_KEY_Y) == GLFW_PRESS;
		break;
	case KeyCode::Z:
		return glfwGetKey(Window::get_window(), GLFW_KEY_Z) == GLFW_PRESS;
		break;
	case KeyCode::SPACE:
		return glfwGetKey(Window::get_window(), GLFW_KEY_SPACE) == GLFW_PRESS;
		break;
	case KeyCode::ESCAPE:
		return glfwGetKey(Window::get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS;
		break;
	default:
		break;
	}

	return false;
}

double Input::get_axis(InputAxis p_axis)
{
	switch (p_axis)
	{
	case InputAxis::MOUSE_X:
		return cursor_x - last_cursor_x;
		break;
	case InputAxis::MOUSE_Y:
		return cursor_y - last_cursor_y;
		break;
	case InputAxis::SCROLL_X:
		return cursor_scroll_x;
		break;
	case InputAxis::SCROLL_Y:
		return cursor_scroll_y;
		break;
	default:
		break;
	}

	return 0;
}

bool Input::get_button(unsigned int p_button)
{
	switch (p_button)
	{
	case 0:
		return glfwGetMouseButton(Window::get_window(), GLFW_MOUSE_BUTTON_1);
		break;
	case 1:
		return glfwGetMouseButton(Window::get_window(), GLFW_MOUSE_BUTTON_2);
	default:
		break;
	}

	return false;
}
