#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"

#include <iostream>
#include <vector>
#include <optional>
#include <set>

using namespace std;

namespace QueueFamilies {
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        
        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    
    class QueueFamiliesManager {
    public:
        static QueueFamilyIndices findQueueFamilies(Device* device);
        static vector<VkDeviceQueueCreateInfo> getQueueInfos(QueueFamilyIndices indices);
    };
}
