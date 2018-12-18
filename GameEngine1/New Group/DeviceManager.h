#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "WindowManager.h"
#include "ValidationLayersManager.h"

#include <iostream>
#include <vector>

using namespace std;

class DeviceManager {
private:
    shared_ptr<WindowManager> world_window = nullptr;
    ValidationLayersManager validationLayersManager =* new ValidationLayersManager();
    VkInstance instance;
    
private:
    void createInstance();
    vector<const char*> getRequiredExtensions();
    VkInstanceCreateInfo instanceCreateInfo();
    
public:
    GLFWwindow* getWindow();
    void initDevice();
    void cleanup();
};
