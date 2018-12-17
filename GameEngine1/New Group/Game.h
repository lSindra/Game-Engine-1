#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "FileReader.hpp"
#include "DeviceManager.h"
#include "WindowManager.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

using namespace std;

class Game {
public:
    
    
private:
    shared_ptr<WindowManager> world_window = nullptr;
    shared_ptr<DeviceManager> world_device = nullptr;
public:
    Game();
    
    void run();
    
private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
};
