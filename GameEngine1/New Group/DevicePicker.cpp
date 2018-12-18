#include "DevicePicker.h"

void DevicePicker::pickPhysicalDevice(VkInstance instance, VkPhysicalDevice physicalDevice) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    
    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }
    
    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

bool DevicePicker::isDeviceSuitable(VkPhysicalDevice physicalDevice) {
    QueueFamilyIndices indices = QueueFamiliesManager::findQueueFamilies(physicalDevice);
    
    return indices.isComplete();
}
