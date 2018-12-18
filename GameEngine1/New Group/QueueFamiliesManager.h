#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>
#include <optional>

using namespace std;

namespace QueueFamilies {
    struct QueueFamilyIndices {
        optional<uint32_t> graphicsFamily;
        
        bool isComplete() {
            return graphicsFamily.has_value();
        }
    };
    
    class QueueFamiliesManager {
    public:
        static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice* physicalDevice);
        static VkDeviceQueueCreateInfo getQueueInfo(VkPhysicalDevice* physicalDevice);
    };
}
