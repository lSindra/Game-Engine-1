#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "FileReader.h"
#include "SwapChainManager.h"
#include "WindowManager.h"
#include "QueueFamiliesManager.h"
#include "GameLogic.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

using namespace Game;

void WindowManager::createSurface() {
    if (glfwCreateWindowSurface(instanceManager.instance, window, nullptr, &surface) != VK_SUCCESS) {
//        throw runtime_error("failed to create window surface!");
    }
}

void WindowManager::initWindow() {
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}
