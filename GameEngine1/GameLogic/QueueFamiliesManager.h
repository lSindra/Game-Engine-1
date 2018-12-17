#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <optional>

class QueueFamiliesManager {
public:
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        
        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    
public:
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    VkQueue graphicsQueue;
    VkQueue presentQueue;
};
