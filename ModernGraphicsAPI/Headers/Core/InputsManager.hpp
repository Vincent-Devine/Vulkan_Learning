#pragma once

#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Common.hpp"

namespace Core
{
	class InputsManager
	{
		// Attribute
	private:
		double mouseX, mouseY;
		float mouseDeltaX, mouseDeltaY;
		bool mouseCaptured;
		unsigned int timeMouseCaptured;

		// Methode
	public:
		InputsManager();

		const CameraInputs Update(GLFWwindow* p_window);
	};
}
