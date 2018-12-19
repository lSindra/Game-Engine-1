#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class Device {
    private:
        VkInstance instance;
        VkSurfaceKHR surface;
        VkQueue graphicsQueue;
        VkDevice device;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceProperties gpu_properties = {};
};
