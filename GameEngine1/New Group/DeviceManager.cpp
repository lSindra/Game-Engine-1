#include "DeviceManager.h"

const vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

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

void DeviceManager::createInstance() {
    if (validationLayersManager.isValidationLayersEnabled() && !validationLayersManager.checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    
    VkApplicationInfo appInfo = instanceAppInfo();
    
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    
    if (validationLayersManager.isValidationLayersEnabled()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

GLFWwindow* DeviceManager::getWindow() {
    return windowManager.window;
}

vector<const char*> DeviceManager::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    
    if (validationLayersManager.isValidationLayersEnabled()) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    
    return extensions;
}

void DeviceManager::initDevice() {
    windowManager.initWindow();
    createInstance();
    validationLayersManager.setupDebugCallback(instance);
    DevicePicker::pickPhysicalDevice(instance, &physicalDevice);
    DevicePicker::createLogicalDevice(instance, &physicalDevice, &device, graphicsQueue);
}

void DeviceManager::cleanup() {
    vkDestroyDevice(device, nullptr);
    
    validationLayersManager.cleanup();
    
    vkDestroyInstance(instance, nullptr);
    
    windowManager.destroyWindow();
}
