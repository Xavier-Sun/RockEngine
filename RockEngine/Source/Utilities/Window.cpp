#include "Window.h"

GLFWwindow* Window::window = nullptr;
int Window::init_width = 0;
int Window::init_height = 0;

GLFWwindow* Window::get_window()
{
    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::init(int p_width, int p_height, const char* p_title)
{
    window = glfwCreateWindow(p_width, p_height, p_title, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    init_width = p_width;
    init_height = p_height;
}

bool Window::is_active()
{
    return !glfwWindowShouldClose(window);
}

void Window::set_active(bool p_active)
{
    glfwSetWindowShouldClose(window, !p_active);
}

int Window::get_width()
{
    int width = 0;
    int height = 0;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int Window::get_height()
{
    int width = 0;
    int height = 0;
    glfwGetWindowSize(window, &width, &height);
    return height;
}

int Window::get_init_width()
{
    return init_width;
}

int Window::get_init_height()
{
    return init_height;
}

void Window::swap_buffers()
{
    glfwSwapBuffers(window);
}

void Window::destroy()
{
    glfwDestroyWindow(window);
}
