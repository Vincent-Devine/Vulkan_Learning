#include "Engine.hpp"

namespace Core
{
	void Engine::Awake()
	{

	}

	void Engine::Start()
	{
		GameObject gameobject;
		gameobject.Init("Resources/Meshs/viking_room.obj", "Resources/Textures/viking_room.png");
		gameobject.position = glm::vec3(1.f, -.5f, -5.f);
		gameobject.rotation = glm::vec3(-90.f, 225.f, 0.f);
		gameobjects.push_back(gameobject);

		GameObject gameobject2;
		gameobject2.Init("Resources/Meshs/cube.obj", "Resources/Textures/woodTexture.jpg");
		gameobject2.position = glm::vec3(-1.2f, -.2f, -5.f);
		gameobject2.scale = glm::vec3(.5f, .5f, .5f);
		gameobjects.push_back(gameobject2);

		ambientLight.ambient = glm::vec3(1.f, 0.f, 0.f);
		ambientLight.diffuse= glm::vec3(1.f, 0.f, 0.f);
		ambientLight.specular = glm::vec3(1.f, 0.f, 0.f);
		ambientLight.direction = glm::vec3(1.f, 0.f, 0.f);
	}

	void Engine::Update(const float p_deltaTime, const unsigned int p_width, const unsigned int p_height, const CameraInputs& p_inputs)
	{
		camera.Update(p_deltaTime, p_width, p_height, p_inputs);
		gameobjects[1].Rotate(glm::vec3(-90.f, 25.f * p_deltaTime, 0.f));
	}

	void Engine::Destroy()
	{

	}
}