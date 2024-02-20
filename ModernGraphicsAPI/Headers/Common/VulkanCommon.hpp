#pragma once

#include <optional>
#include <vector>
#include <string>
#include <array>

#include <vulkan/vulkan.h>

#include "Common.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

namespace Common
{
    struct VulkanCommonInit
    {
        GLFWwindow* window;
        const unsigned int width;
        const unsigned int height;
        std::vector<Core::GameObject> gameobjects;
    };

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class VulkanCommon
    {
        // ----------
        // Attributes
        // ----------
    public:
        bool framebufferResized = false;
        GLFWwindow* window = nullptr;

    private:
        VkInstance instance;
        unsigned int WIDTH;
        unsigned int HEIGHT;
        const unsigned int MAX_FRAMES_IN_FLIGHT = 2;

        // Layers
        const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
        bool enableValidationLayers;

        // Physical Device (GPU)
        VkPhysicalDevice physicalDevice;

        // Logical Device
        VkDevice logicalDevice;
        VkQueue graphicsQueue;
        const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

        // Debug
        VkDebugUtilsMessengerEXT callback;

        // Surface
        VkSurfaceKHR surface;

        // Presentation Queue
        VkQueue presentQueue;

        // SwapChain
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        // Image Veiw
        std::vector<VkImageView> swapChainImageViews;

        // Pipeline layout
        VkPipelineLayout pipelineLayout;

        // Render Pass
        VkRenderPass renderPass;

        // Graphics Pipeline
        VkPipeline graphicsPipeline;

        // Framebuffer
        std::vector<VkFramebuffer> swapChainFramebuffers;

        // Command Pool 
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        // Semaphore
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        uint32_t currentFrame = 0;

        // Description layout
        VkDescriptorSetLayout descriptorSetLayout;

        unsigned int nbGameObject;

        std::vector<VkBuffer> vertexBuffers;
        std::vector<VkDeviceMemory> vertexBufferMemorys;
        std::vector<VkBuffer> indexBuffers;
        std::vector<VkDeviceMemory> indexBufferMemorys;

        std::vector<std::vector<VkBuffer>> uniformBuffers;
        std::vector<std::vector<VkDeviceMemory>> uniformBuffersMemory;
        std::vector<std::vector<void*>> uniformBuffersMapped;

        std::vector<VkDescriptorPool> descriptorPools;
        std::vector<std::vector<VkDescriptorSet>> descriptorSets;

        // Texture Mapping
        std::vector<VkImage> textureImages;
        std::vector<VkDeviceMemory> textureImageMemorys;
        std::vector<VkImageView> textureImageViews;
        std::vector<VkSampler> textureSamplers;
        std::vector<uint32_t> indicesSizes;

        // Depth buffering
        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;


        // -------
        // Methods
        // -------
    public:
        ~VulkanCommon();

        bool Init(VulkanCommonInit& p_vulkanCommonInit);
        void DrawFrame(const Core::Camera& p_camera, const std::vector<Core::GameObject> p_gameObjects);

        VkDevice& GetDevice() { return logicalDevice; };

    private:
        void CreateInstance();

        // Physical Device (GPU)
        void PickPhysicalDevice();
        int RateDeviceSuitability(VkPhysicalDevice p_device);
        bool CheckDeviceExtensionSupport(VkPhysicalDevice p_device);

        // Queue Family
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice p_device);

        // Layers
        bool CheckValidationLayerSupport();

        // Extensions
        std::vector<const char*> GetRequiredExtention();

        // Debug
        void SetupDebugMessenger();
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT p_messageSeverity, 
                                                            VkDebugUtilsMessageTypeFlagsEXT p_messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* p_callbackData,
                                                            void* p_userData);
        VkResult CreateDebugUtilsMessengerEXT(VkInstance p_instance, 
                                              const VkDebugUtilsMessengerCreateInfoEXT* p_createInfo, 
                                              const VkAllocationCallbacks* p_allocator, 
                                              VkDebugUtilsMessengerEXT* p_callback);
        void DestroyDebugUtilsMessengerEXT(VkInstance p_instance, 
                                           VkDebugUtilsMessengerEXT p_callback, 
                                           const VkAllocationCallbacks* p_allocator);
        void GetCreateInfoDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT& p_createInfo);

        // Logical Device
        void CreateLogicalDevice();

        // Surface
        void CreateSurface(GLFWwindow* p_window);

        // SwapChain
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice p_device);
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& p_availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& p_availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& p_capabilities);
        void CreateSwapChain();
        void CleanupSwapChain();
        void RecreateSwapChain();

        // Image View
        void CreateImageViews();

        // Graphique Pipeline
        void CreateGraphiquePipeline();
        static std::vector<char> ReadFile(const std::string& p_filename);
        VkShaderModule CreateShaderModule(const std::vector<char>& p_code);

        // Render Pass
        void CreateRenderPass();

        // Framebuffer
        void CreateFramebuffer();

        // Command Pool
        void CreateCommandPool();
        void CreateCommandBuffers();
        void RecordCommandBuffer(VkCommandBuffer p_commandBuffer, uint32_t p_imageIndex);

        // SyncObject
        void CreateSyncObjects();

        // Buffer
        void CreateVertexBuffer(const Core::GameObject& p_gameobject, const unsigned int p_index);
        uint32_t FindMemoryType(uint32_t p_typeFilter, VkMemoryPropertyFlags p_properties);
        void CreateBuffer(VkDeviceSize p_size, VkBufferUsageFlags p_usage, VkMemoryPropertyFlags p_properties, VkBuffer& p_buffer, VkDeviceMemory& p_bufferMemory);
        void CopyBuffer(VkBuffer p_srcBuffer, VkBuffer p_dstBuffer, VkDeviceSize p_size);
        void CreateIndexBuffer(const Core::GameObject& p_gameobject, const unsigned int p_index);

        VkCommandBuffer BeginSingleTimeCommands();
        void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

        void CreateUniformBuffer(const unsigned int p_index);
        void UpdateUniformBuffer(uint32_t p_currentImage, const Core::Camera& p_camera, const std::vector<Core::GameObject> gameObjects);
        void CreateDescriptorPool(const unsigned int p_index);
        void CreateDescriptorSets(const unsigned int p_index);

        // Description Layout
        void CreateDescriptionSetLayout();

        // Texture Mapping
        void CreateTextureImage(Core::GameObject& p_gameobject, const unsigned int p_index);
        void CreateImage(uint32_t p_width, uint32_t p_height, VkFormat p_format, VkImageTiling p_tiling, VkImageUsageFlags p_usage, VkMemoryPropertyFlags p_properties, VkImage& p_image, VkDeviceMemory& p_imageMemory);
        void TransitionImageLayout(VkImage p_image, VkFormat p_format, VkImageLayout p_oldLayout, VkImageLayout p_newLayout);
        void CopyBufferToImage(VkBuffer p_buffer, VkImage p_image, uint32_t p_width, uint32_t p_height);
        void CreateTextureImageView(const unsigned int p_index);
        VkImageView CreateImageView(VkImage p_image, VkFormat p_format, VkImageAspectFlags p_aspectFlags);
        void CreateTextureSampler(const unsigned int p_index);

        // Depth buffering
        void CreateDepthResources();
        VkFormat FindSupportedFormat(const std::vector<VkFormat>& p_candidates, VkImageTiling p_tiling, VkFormatFeatureFlags p_features);
        VkFormat FindDepthFormat();
        bool HasStencilComponent(VkFormat p_format);
    };
}