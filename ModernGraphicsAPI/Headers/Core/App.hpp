#pragma once

#include "VulkanCommon.hpp"
#include "Window.hpp"
#include "Engine.hpp"

namespace Core
{
    class App
    {
        // ----------
        // Attributes
        // ----------
    private:
        static App* singleton;
        
        Common::Window window;
        Common::VulkanCommon vulkanCommon;
        Engine engine;
        
        GLFWwindow* glfwWindow;

        // -------
        // Methods
        // -------
    public:
        static void Create();
        static void Destroy();
        
        static App* Get();

        int Run(const std::string& p_windowName, const unsigned int p_width, const unsigned int p_height);

        void Quit();

        void FrameBufferWasBeenResized() { vulkanCommon.framebufferResized = true; };

    private:
        bool Init(const std::string& p_windowName, const unsigned int p_width, const unsigned int p_height);
        void Release();
    };
}