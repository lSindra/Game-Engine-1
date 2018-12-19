#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "QueueFamiliesManager.h"
#include "ValidationLayersManager.h"
#include "Device.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace QueueFamilies;

class DevicePicker {
public:
    static VkDeviceQueueCreateInfo getQueueInfo(VkPhysicalDevice physicalDevice);
    
    static void createLogicalDevice(Device* device);
    static void pickPhysicalDevice(Device* device);
    static bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface);
};
