#include "Window.hpp"

#include "Assertion.hpp"
#include "App.hpp"

static void onError(int p_error, const char* p_description)
{
    Log::Print(p_description, LogLevel::Critical);
}

static void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    Core::App::Get()->FrameBufferWasBeenResized();
}

namespace Common
{
    GLFWwindow* Window::Create(const std::string& p_windowName, const unsigned int p_width, const unsigned int p_height)
	{
        windowName = p_windowName;
        width = p_width;
        height = p_height;

        glfwSetErrorCallback(onError);

        Assertion(glfwInit() == true, "GLFW counld'nt init.");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            Assertion(false,"GLFW couldn't create window.");
        }

        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

        return window;
	}

    const CameraInputs Window::Update()
    {
        return inputsManager.Update(window);
    }

	void Window::Destroy()
	{
        glfwDestroyWindow(window);
        glfwTerminate();
	}
}