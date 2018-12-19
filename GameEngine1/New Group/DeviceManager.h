#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "WindowManager.h"
#include "ValidationLayersManager.h"
#include "DevicePicker.h"
#include "Renderer.h"
#include "Device.h"
#include "GraphicsPipeline.h"

#include <iostream>
#include <vector>

using namespace std;

class DeviceManager {
private:
    WindowManager windowManager =* new WindowManager();
    ValidationLayersManager validationLayersManager = ValidationLayersManager::getInstance();
    
    Device* device;
    
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
