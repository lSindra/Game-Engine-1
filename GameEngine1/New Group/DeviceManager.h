#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "WindowManager.h"
#include "ValidationLayersManager.h"
#include "DevicePicker.h"
#include "Device.h"

#include <iostream>
#include <vector>

using namespace std;

class DeviceManager {
private:
    WindowManager windowManager =* new WindowManager();
    ValidationLayersManager validationLayersManager = ValidationLayersManager::getInstance();
    
    VkInstance instance;
    VkSurfaceKHR surface;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkDevice logicalDevice;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties gpu_properties = {};
    
    Device device;
    
private:
    void createInstance();
    void createSurface();
    vector<const char*> getRequiredExtensions();
    VkInstanceCreateInfo instanceCreateInfo();
    
public:
    GLFWwindow* getWindow();
    void initDevice();
    void cleanup();
};
