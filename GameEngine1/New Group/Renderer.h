#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"

class Renderer {
public:
    static void createImageViews(Device* device);
    static void createRenderPass(Device* device);
};
