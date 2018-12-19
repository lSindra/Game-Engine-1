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
    
    if (vkCreateInstance(&createInfo, nullptr, &device->instance) != VK_SUCCESS) {
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

void DeviceManager::createSurface()
{
    if (glfwCreateWindowSurface(device->instance, windowManager.window, nullptr, &device->surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void DeviceManager::initDevice() {
    device = new Device();
    windowManager.initWindow();
    createInstance();
    validationLayersManager.setupDebugCallback(device->instance);
    createSurface();
    DevicePicker::pickPhysicalDevice(device);
    DevicePicker::createLogicalDevice(device);
    DevicePicker::createSwapChain(device);
    Renderer::createImageViews(device);
    GraphicsPipeline::createGraphicsPipeline(device);
}

static void cleanupSwapChain(Device *device) {
    for (auto imageView : device->swapChain.swapChainImageViews) {
        vkDestroyImageView(device->logicalDevice, imageView, nullptr);
    }
    
    vkDestroySwapchainKHR(device->logicalDevice, device->swapChain.swapChainKHR, nullptr);
}

void DeviceManager::cleanup() {
    cleanupSwapChain(device);
    
    vkDestroyDevice(device->logicalDevice, nullptr);
    
    validationLayersManager.cleanup();
    
    vkDestroySurfaceKHR(device->instance, device->surface, nullptr);
    
    vkDestroyInstance(device->instance, nullptr);
    
    windowManager.destroyWindow();
}
