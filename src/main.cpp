#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }
private:
    // creating a glfw window instance
    GLFWwindow* window = nullptr;
    // creating the vulkan instance
    VkInstance instance;

    void initWindow()
    {
        glfwInit();  // initializing glfw this have to pair with glfwTerminta()
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, false);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); // creating a pointer to a glfw window
    }

    void createInstance()
    {
        VkApplicationInfo appInfo{}; // this is a struct
        // as all vulkan structs we start by filling the data
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
    }

    void initVulkan()
    {
        createInstance();
    }
    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }
    void cleanup()
    {
        glfwDestroyWindow(window);  // destroying pointer created on initWindow
        glfwTerminate();  // closing glfw end of glfwInit()
    }

};

int main()
{
    // create the instance of the app
    HelloTriangleApplication app;
    try
    {
        app.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    } 
    return EXIT_SUCCESS;
}