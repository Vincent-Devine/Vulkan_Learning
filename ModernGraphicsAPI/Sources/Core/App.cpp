#include "App.hpp"
#include "Assertion.hpp"

static void onInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

namespace Core
{
    App* App::singleton = nullptr;

    void App::Create()
    {
        singleton->Run("Modern Graphics API", 800, 600);
    }

    void App::Destroy()
    {
        singleton->Release();
        delete singleton;
    }

    App* App::Get()
    {
        if (singleton == nullptr)
            singleton = new App{};
        return singleton;
    }

    int App::Run(const std::string& p_windowName, const unsigned int p_width, const unsigned int p_height)
    {
        Assertion(Init(p_windowName, p_width, p_height), "Failed to Init app.");

        static auto startTime = std::chrono::high_resolution_clock::now();


        while (!glfwWindowShouldClose(glfwWindow))
        {
            glfwPollEvents();

            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

            engine.Update(deltaTime, p_width, p_height, window.Update());

            vulkanCommon.DrawFrame(engine.camera, engine.gameobjects);
        }

        vkDeviceWaitIdle(vulkanCommon.GetDevice());

        return 0;
    }

    void App::Quit()
    {

    }

    bool App::Init(const std::string& p_windowName, const unsigned int p_width, const unsigned int p_height)
    {
        glfwWindow = window.Create(p_windowName, p_width, p_height);
        glfwSetKeyCallback(glfwWindow, onInput);

        engine.Awake();
        engine.Start();

        Common::VulkanCommonInit vulkanCommonInit
        {
            glfwWindow,
            p_width,
            p_height,
            engine.gameobjects
        };

        bool res = vulkanCommon.Init(vulkanCommonInit);

        Log::Print("Init finish", LogLevel::Notification);
        return res;
    }

    void App::Release()
    {
        window.Destroy();
        engine.Destroy();
    }
}