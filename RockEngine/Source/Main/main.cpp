#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Utilities\Window.h>
#include <System\System.h>
#include <System\InputSystem.h>
#include <System\TimeSystem.h>
#include <System\EditorCameraSystem.h>
#include <System\RenderSystem.h>
#include <Component\EditorUI.h>
#include <stb_image.h>

int main()
{
	if (glfwInit() == GL_FALSE)
	{
		std::cout << "Failed to load GLFW." << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window::init(1600, 900, "Rock Engine 0.1 - by Xavier");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load GLAD." << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	stbi_set_flip_vertically_on_load(true);

	System::add_system<InputSystem>();
	System::add_system<TimeSystem>();
	System::add_system<EditorCameraSystem>();
	System::add_system<RenderSystem>();
	System::init_all();
	EditorUI::init();

	while (Window::is_active())
	{
		System::update_all();
		EditorUI::update();
		glfwPollEvents();
		Window::swap_buffers();
	}

	glfwTerminate();

	return 0;
}
