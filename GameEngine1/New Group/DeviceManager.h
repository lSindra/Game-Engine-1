#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "WindowManager.h"

#include <iostream>

using namespace std;

class DeviceManager {
private:
    shared_ptr<WindowManager> world_window = nullptr;
    VkInstance instance = VK_NULL_HANDLE;
    
    void createInstance();
    
public:
    GLFWwindow* getWindow();
    void initDevice();
    void cleanup();
};
