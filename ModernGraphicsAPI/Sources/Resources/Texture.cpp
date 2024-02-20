#include "Texture.hpp"

#include "Assertion.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Resources
{
	void Texture::Init(const std::string& p_path)
	{
		path = p_path;

		pixel = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		Assertion(pixel, "Failed to load texture image.");
	}

	void Texture::Release()
	{
		stbi_image_free(pixel);
	}
}