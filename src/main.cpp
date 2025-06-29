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
    VkInstance instance;  // this instance will be used as reference and could be changed to a pointer if needed.

    void initWindow()
    {
        glfwInit();  // initializing glfw this have to pair with glfwTerminta()
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, false);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); // creating a pointer to a glfw window
    }

    void createInstance()
    {
        VkApplicationInfo appInfo{}; // this is a struct this will be used in create info structure bellow
        // as all vulkan structs we start by filling the data
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;  // pointing to VkApplication info appInfo created above.

        // creating variables to hold glfw extension count and glfw Extension's names.
        uint32_t glfwExtensionCount = 0; // will hold the extension count out of glfwGetRequiredInstanceExtensions function.
        const char** glfwExtensions;  // will hold the extension names as characters constant string. 
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); // out value passed by reference.
        // filling the information for the VkInstanceCreateInfo created above.
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;
        // creates the instance using the createInfo structure, and returns the instance as an output paramenter.
        if (
            vkCreateInstance(
                &createInfo, // pointer to creation info structure. 
                nullptr, // pointer to custom allocator callbacks, null this vulkan tutorial 
                &instance // pointer to the instance
                ) != VK_SUCCESS 
            )
            throw std::runtime_error("failed to create instance!");
        else
            {
                std::cout << "instance successfully created" << "\n";
            }
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
        // destroying the vulkan instance
        vkDestroyInstance(instance, nullptr); 
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