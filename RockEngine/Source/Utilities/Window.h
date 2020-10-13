#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	static GLFWwindow* window;
	static int init_width;
	static int init_height;

	Window() = delete;

public:
	static GLFWwindow* get_window();
	static void init(int p_width, int p_height, const char* p_title);
	static bool is_active();
	static void set_active(bool p_active);
	static int get_width();
	static int get_height();
	static int get_init_width();
	static int get_init_height();
	static void swap_buffers();
	static void destroy();
};

#endif