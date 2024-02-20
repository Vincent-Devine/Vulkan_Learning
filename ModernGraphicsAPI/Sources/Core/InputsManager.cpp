#include "InputsManager.hpp"

namespace Core
{
	InputsManager::InputsManager()
		: mouseX(0.0)
		, mouseY(0.0)
		, mouseDeltaX(0.f)
		, mouseDeltaY(0.f)
		, mouseCaptured(false)
		, timeMouseCaptured(0)
	{
	}

	const CameraInputs InputsManager::Update(GLFWwindow* p_window)
	{
		CameraInputs inputs;

		// Camera inputs (keyboard)
		if (glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
			inputs.moveForward = true;
		else
			inputs.moveForward = false;

		if (glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
			inputs.moveBackward = true;
		else
			inputs.moveBackward = false;

		if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
			inputs.moveLeft = true;
		else
			inputs.moveLeft = false;

		if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
			inputs.moveRight = true;
		else
			inputs.moveRight = false;

		if (glfwGetKey(p_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			inputs.moveDown = true;
		else
			inputs.moveDown = false;

		if (glfwGetKey(p_window, GLFW_KEY_SPACE) == GLFW_PRESS)
			inputs.moveUp = true;
		else
			inputs.moveUp = false;

		// Camera inputs (mouse)
		if (glfwGetKey(p_window, GLFW_KEY_M) == GLFW_PRESS)
			mouseCaptured = false;

		if (glfwGetMouseButton(p_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			mouseCaptured = true;
			//glfwSetCursorPos(window, (width / 2), (height / 2));
			glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			timeMouseCaptured++;
		}
		else
		{
			mouseCaptured = false;
			timeMouseCaptured = 0;
			glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		if (mouseCaptured)
		{
			double newMouseX, newMouseY;
			glfwGetCursorPos(p_window, &newMouseX, &newMouseY);
			mouseDeltaX = (float)(newMouseX - mouseX);
			mouseDeltaY = (float)(newMouseY - mouseY);
			mouseX = newMouseX;
			mouseY = newMouseY;

			if (timeMouseCaptured == 1) // firstFrame
			{
				inputs.deltaX = 0.f;
				inputs.deltaY = 0.f;
			}
			else
			{
				inputs.deltaX = mouseDeltaX;
				inputs.deltaY = mouseDeltaY;
			}
		}
		else
		{
			inputs.deltaX = 0.f;
			inputs.deltaY = 0.f;
		}

		return inputs;
	}
}
