#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"
#include "SwapChainManager.h"
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

using namespace std;

class Renderer {
public:
    bool framebufferResized = false;
    
private:
    const int MAX_FRAMES_IN_FLIGHT = 2;

    size_t currentFrame = 0;
    vector<VkFence> inFlightFences;
    vector<VkSemaphore> imageAvailableSemaphores;
    vector<VkSemaphore> renderFinishedSemaphores;
    
private:
    void updateUniformBuffer(Device* device, uint32_t imageIndex);
    
public:
    void createSemaphores(Device* device);
    void drawFrame(Device* device);
    void cleanup(Device* device);
};
