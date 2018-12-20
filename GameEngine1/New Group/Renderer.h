#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"

using namespace std;

class Renderer {
private:
    const int MAX_FRAMES_IN_FLIGHT = 2;

    size_t currentFrame = 0;
    vector<VkFence> inFlightFences;
    vector<VkSemaphore> imageAvailableSemaphores;
    vector<VkSemaphore> renderFinishedSemaphores;
    
public:
    void createSemaphores(Device* device);
    void drawFrame(Device* device);
    void cleanup(Device* device);
};
