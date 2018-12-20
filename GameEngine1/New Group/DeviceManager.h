#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "WindowManager.h"
#include "ValidationLayersManager.h"
#include "DevicePicker.h"
#include "Renderer.h"
#include "Device.h"
#include "SwapChainManager.h"

#include <iostream>
#include <vector>

using namespace std;

class DeviceManager {
private:
    WindowManager* windowManager = WindowManager::getInstance();
    ValidationLayersManager* validationLayersManager = ValidationLayersManager::getInstance();
    
    Device* device;
    
private:
    void createInstance();
    void createSurface();
    vector<const char*> getRequiredExtensions();
    VkInstanceCreateInfo instanceCreateInfo();
    
public:
    Device* getDevice();
    void initDevice();
    void cleanupSwapChain();
    void cleanup();
};
