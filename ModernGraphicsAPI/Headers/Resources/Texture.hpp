#pragma once

#include <string>

#include <stb_image.h>

namespace Resources
{
	class Texture
	{
		// ---------
		// Attribute
		// ---------
	public:
		stbi_uc* pixel;
		int texWidth;
		int texHeight;
		int texChannels;
	private:
		std::string path;

		// -------
		// Methods
		// -------
	public:
		void Init(const std::string& p_path);
		void Release();
	};
}