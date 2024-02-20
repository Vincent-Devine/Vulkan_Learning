#pragma once

#include <vector>

#include "GameObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"

namespace Core
{
	class Engine
	{
		// ----------
		// Attributes
		// ----------
	public:
		std::vector<GameObject> gameobjects;
		Camera camera;
		AmbientLight ambientLight;
		SpotLight spotLight;
		PointLight pointLight;

		// -------
		// Methods
		// -------
	public:
		void Awake();
		void Start();
		void Update(const float p_deltaTime, const unsigned int p_width, const unsigned int p_height, const CameraInputs& p_inputs);
		void Destroy();
	};
}