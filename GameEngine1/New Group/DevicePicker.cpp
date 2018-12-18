#include "DevicePicker.h"

void DevicePicker::pickPhysicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    
    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            *physicalDevice = device;
            break;
        }
    }
    
    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

bool DevicePicker::isDeviceSuitable(VkPhysicalDevice physicalDevice) {
    QueueFamilyIndices indices = QueueFamiliesManager::findQueueFamilies(&physicalDevice);
    
    return indices.isComplete();
}

//happens here
void DevicePicker::createLogicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice, VkDevice device, VkQueue graphicsQueue) {
    VkDeviceQueueCreateInfo queueCreateInfo = QueueFamiliesManager::getQueueInfo(physicalDevice);
    
    VkPhysicalDeviceFeatures deviceFeatures = {};
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    
    createInfo.pEnabledFeatures = &deviceFeatures;
    
    createInfo.enabledExtensionCount = 0;
    
//    if (enableValidationLayers) {
//        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//        createInfo.ppEnabledLayerNames = validationLayers.data();
//    } else {
//        createInfo.enabledLayerCount = 0;
//    }
    
    if (vkCreateDevice(*physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    
    vkGetDeviceQueue(device, queueCreateInfo.queueFamilyIndex, 0, &graphicsQueue);
}
