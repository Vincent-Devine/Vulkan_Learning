#pragma once

#include "glm/glm.hpp"

class Light
{
	// ---------
	// Attribute
	// ---------
public:
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class AmbientLight : public Light
{
	// ---------
	// Attribute
	// ---------
public:
	glm::vec3 direction;
};

class PointLight : public Light
{
	// ---------
	// Attribute
	// ---------
public:
	float constant;
	float linear;
	float quadratic;
};

class SpotLight : public Light
{
	// ---------
	// Attribute
	// ---------
public:
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;
};