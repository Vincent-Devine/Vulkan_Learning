#pragma once

#define SUCCESS 0
#define FAILURE 1
#define DEBUG

#include <array>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

class Vertex
{
    // ----------
    // Attributes
    // ----------
public:
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    // -------
    // Methods
    // -------
public:
    static VkVertexInputBindingDescription GetBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions();
    bool operator==(const Vertex& other) const;
};

class UniformBufferObject
{
    // ----------
    // Attributes
    // ----------
public:
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

struct CameraInputs
{
    float deltaX = 0.f;
    float deltaY = 0.f;
    bool moveForward = true;
    bool moveBackward = true;
    bool moveRight = true;
    bool moveLeft = true;
    bool moveUp = true;
    bool moveDown = true;
};