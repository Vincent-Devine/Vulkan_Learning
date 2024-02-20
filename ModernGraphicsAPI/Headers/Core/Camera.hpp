#pragma once

#include "Common.hpp"

namespace Core
{
	class Camera
	{
		// ---------
		// Attribute
		// ---------
	public:
		UniformBufferObject ubo;

	private:
		glm::vec3 position;
		glm::vec3 rotation;
		float speed = 0.1f;

		// -------
		// Methods
		// -------
	public:
		void Update(const float p_deltaTime, const float p_width, const float p_height, const CameraInputs& p_inputs);
	
	private:
		void CalcInputs(const float p_deltaTime, const CameraInputs& p_inputs);
		void CalcView();
	};
}