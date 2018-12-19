#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "QueueFamiliesManager.h"
#include "ValidationLayersManager.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace QueueFamilies;

class DevicePicker {
public:
    static VkDeviceQueueCreateInfo getQueueInfo(VkPhysicalDevice physicalDevice);
    
    static void createLogicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice, VkDevice device, VkQueue graphicsQueue);
    static void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice);
    static bool isDeviceSuitable(VkPhysicalDevice physicalDevice);
};
