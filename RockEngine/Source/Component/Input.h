#ifndef INPUT_H
#define INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utilities\Window.h"
#include "Component.h"

enum class KeyCode
{
	A, B, C, D, E, F, G, H, I, J, K, L, M,
	N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	SPACE, ESCAPE
};

enum class InputAxis
{
	MOUSE_X,
	MOUSE_Y,
	SCROLL_X,
	SCROLL_Y
};

class Input : public Component
{
private:
	static double last_cursor_x;
	static double last_cursor_y;
	static double cursor_x;
	static double cursor_y;
	static double cursor_scroll_x;
	static double cursor_scroll_y;

public:
	static bool get_key(KeyCode p_key_code);
	static double get_axis(InputAxis p_axis);
	static bool get_button(unsigned int p_button);

private:
	Input() : Component(nullptr) {}

public:
	virtual ~Input() override {}

	Input(const Input&) = delete;

	Input& operator=(const Input&) = delete;

private:
	friend void scroll_callback(GLFWwindow* window, double offset_x, double offset_y);

	friend class InputSystem;
};

#endif