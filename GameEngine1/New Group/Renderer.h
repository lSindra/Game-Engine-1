#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"
#include "QueueFamiliesManager.h"

using namespace QueueFamilies;

class Renderer {
public:
    static void createImageViews(Device* device);
    static void createRenderPass(Device* device);
    static void createCommandPool(Device* device);
    static void createCommandBuffers(Device* device);
    static void drawFrame(Device* device);
};
