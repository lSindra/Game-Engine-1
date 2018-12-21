#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"
#include "FileReader.h"
#include "Shaders.h"
#include "QueueFamiliesManager.h"

using namespace QueueFamilies;
using namespace Shaders;

class GraphicsPipeline {  
private:
    static void createGraphicsPipeline(Device* device);
    static void createVertexBuffers(Device* device);
    static void createCommandPool(Device* device);
    static void createCommandBuffers(Device* device);
    static void createFrameBuffers(Device* device);
    
public:
    static void create(Device* device);
};
