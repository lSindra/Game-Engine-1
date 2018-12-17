#include "DeviceManager.h"

static VkApplicationInfo instanceAppInfo() {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    return appInfo;
}

static VkInstanceCreateInfo instanceCreateInfo() {
    VkApplicationInfo appInfo = instanceAppInfo();
    
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    
    createInfo.enabledLayerCount = 0;
    return createInfo;
}

void DeviceManager::initDevice() {
    world_window = std::make_shared<WindowManager>();
    world_window->initWindow();
    
    createInstance();
}

void DeviceManager::createInstance() {
    VkInstanceCreateInfo createInfo = instanceCreateInfo();
    
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void DeviceManager::cleanup() {
    world_window->destroyWindow();
}

GLFWwindow* DeviceManager::getWindow() {
    return world_window->window;
}
