#include "DevicePicker.h"

const vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

void DevicePicker::pickPhysicalDevice(Device* device) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(device->instance, &deviceCount, nullptr);
    
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(device->instance, &deviceCount, devices.data());
    
    for (const auto& singleDevice : devices) {
        if (isDeviceSuitable(singleDevice, &device->surface)) {
            device->physicalDevice = singleDevice;
            break;
        }
    }
    
    if (device->physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

static bool checkDeviceForSwapChainSupport(Device* device) {
    bool swapChainAdequate = false;
    SwapChainManager::SwapChainSupportDetails swapChainSupport = SwapChainManager::querySwapChainSupport(device);
    swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    return swapChainAdequate;
}

bool DevicePicker::isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface) {
    Device* tempDevice = new Device();
    tempDevice->physicalDevice = physicalDevice;
    tempDevice->surface = *surface;

    return QueueFamiliesManager::findQueueFamilies(tempDevice).isComplete() &&
            checkDeviceExtensionSupport(tempDevice) &&
            checkDeviceForSwapChainSupport(tempDevice);
}

bool DevicePicker::checkDeviceExtensionSupport(Device* device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device->physicalDevice, nullptr, &extensionCount, nullptr);
    
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device->physicalDevice, nullptr, &extensionCount, availableExtensions.data());
    
    std::set<std::string> requiredExtensions(device->deviceExtensions.begin(), device->deviceExtensions.end());
    
    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }
    
    return requiredExtensions.empty();
}

void DevicePicker::createLogicalDevice(Device* device) {
    ValidationLayersManager* validationLayersManager = ValidationLayersManager::getInstance();
    QueueFamilyIndices indices = QueueFamiliesManager::findQueueFamilies(device);
    vector<VkDeviceQueueCreateInfo> queueCreateInfos = QueueFamiliesManager::getQueueInfos(indices);
    
    VkPhysicalDeviceFeatures deviceFeatures = {};
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(device->deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = device->deviceExtensions.data();
    
    if (validationLayersManager->isValidationLayersEnabled()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    
    if (vkCreateDevice(device->physicalDevice, &createInfo, nullptr, &device->logicalDevice) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    
    vkGetDeviceQueue(device->logicalDevice, indices.graphicsFamily.value(), 0, &device->graphicsQueue);
    vkGetDeviceQueue(device->logicalDevice, indices.presentFamily.value(), 0, &device->presentQueue);
}
