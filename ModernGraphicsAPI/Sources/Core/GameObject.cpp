#include "GameObject.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Core
{
	void GameObject::Init(const std::string& p_meshPath, const std::string& p_texturePath)
	{
		mesh.Init(p_meshPath);
		texture.Init(p_texturePath);
		position = glm::vec3(0.f, 0.f, 0.f);
		rotation = glm::vec3(0.f, 0.f, 0.f);
		scale = glm::vec3(1.f, 1.f, 1.f);
	}

	glm::mat4 GameObject::GetMatrixModel()
	{
		glm::mat4 model(1.f);

		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		model = glm::scale(model, scale);

		return model;
	}

	void GameObject::Rotate(const glm::vec3& p_rotate)
	{
		rotation = p_rotate;
	}
}