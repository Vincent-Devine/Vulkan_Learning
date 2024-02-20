#pragma once

#include "Texture.hpp"
#include "Mesh.hpp"

namespace Core
{
	class GameObject
	{
		// ----------
		// Attributes
		// ----------
	public:
		Resources::Texture texture;
		Resources::Mesh mesh;
		
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		// -------
		// Methods
		// -------
	public:
		void Init(const std::string& p_meshPath, const std::string& p_texturePath);
		glm::mat4 GetMatrixModel();
		void Rotate(const glm::vec3& p_rotate);
	};
}