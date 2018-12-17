#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "DeviceManager.h"

#include <iostream>

using namespace std;

class Game {
    
private:
    shared_ptr<DeviceManager> world_device = nullptr;
    
public:
    void run();
    
private:
    void initVulkan();
    void mainLoop();
    void cleanup();
};
