#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <vector>

class DeviceManager {
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    
public:
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

public:
    void pickPhysicalDevice();
    void createLogicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};
