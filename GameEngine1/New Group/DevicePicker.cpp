#include "DevicePicker.h"

const vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

void DevicePicker::pickPhysicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice, VkSurfaceKHR* surface) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    
    for (const auto& device : devices) {
        if (isDeviceSuitable(device, surface)) {
            *physicalDevice = device;
            break;
        }
    }
    
    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

bool DevicePicker::isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface) {
    QueueFamilyIndices indices = QueueFamiliesManager::findQueueFamilies(&physicalDevice, surface);
    
    return indices.isComplete();
}

void DevicePicker::createLogicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice, VkDevice *device, VkQueue graphicsQueue, VkQueue presentQueue, VkSurfaceKHR* surface) {
    ValidationLayersManager validationLayersManager = ValidationLayersManager::getInstance();
    QueueFamilyIndices indices = QueueFamiliesManager::findQueueFamilies(physicalDevice, surface);
    vector<VkDeviceQueueCreateInfo> queueCreateInfos = QueueFamiliesManager::getQueueInfos(physicalDevice, surface, indices);
    
    VkPhysicalDeviceFeatures deviceFeatures = {};
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;
    
    if (validationLayersManager.isValidationLayersEnabled()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    
    if (vkCreateDevice(*physicalDevice, &createInfo, nullptr, device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    
    vkGetDeviceQueue(*device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(*device, indices.presentFamily.value(), 0, &presentQueue);
}
