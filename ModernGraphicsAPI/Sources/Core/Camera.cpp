#include "Camera.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Core
{
	void Camera::Update(const float p_deltaTime, const float p_width, const float p_height, const CameraInputs& p_inputs)
	{
		CalcInputs(p_deltaTime, p_inputs);
		CalcView();

		ubo.proj = glm::perspective(glm::radians(45.0f), p_width / p_height, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;
	}

	void Camera::CalcInputs(const float p_deltaTime, const CameraInputs& p_inputs)
	{
		speed = 0.001f;
		rotation.y -= p_inputs.deltaX / 6.f;
		rotation.x -= p_inputs.deltaY / 6.f;

		if (rotation.x < -90.f)
			rotation.x = -90.f;

		if (rotation.x > 90.f)
			rotation.x = 90.f;

		if (rotation.y < -360.f)
			rotation.y = 360.f;

		if (rotation.y > 360.f)
			rotation.y = -360.f;

		if (p_inputs.moveForward)
		{
			position.x += speed * cosf(glm::radians(rotation.y + 90.f));
			position.z -= speed * sinf(glm::radians(rotation.y + 90.f));
		}

		if (p_inputs.moveBackward)
		{
			position.x -= speed * cosf(glm::radians(rotation.y + 90.f));
			position.z += speed * sinf(glm::radians(rotation.y + 90.f));
		}

		if (p_inputs.moveLeft)
		{
			position.x -= speed * cosf(glm::radians(rotation.y));
			position.z += speed * sinf(glm::radians(rotation.y));
		}

		if (p_inputs.moveRight)
		{
			position.x += speed * cosf(glm::radians(rotation.y));
			position.z -= speed * sinf(glm::radians(rotation.y));
		}

		if (p_inputs.moveUp)
			position.y += speed;

		if (p_inputs.moveDown)
			position.y -= speed;
	}

	void Camera::CalcView()
	{
		ubo.view = glm::rotate(glm::mat4(1.f), glm::radians(-rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.f), glm::radians(-rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.f), -position);
	}
}