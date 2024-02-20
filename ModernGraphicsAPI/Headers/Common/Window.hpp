#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Common.hpp"
#include "InputsManager.hpp"

namespace Common
{
	class Window
	{
		// ----------
		// Attributes
		// ----------
	private:
		std::string windowName;
		unsigned int width;
		unsigned int height;

		GLFWwindow* window;

		Core::InputsManager inputsManager;

		// -------
		// Methods
		// -------
	public:
		GLFWwindow* Create(const std::string& p_windowName, const unsigned int p_width, const unsigned int p_height);

		const CameraInputs Update();

		void Destroy();
	};
}
