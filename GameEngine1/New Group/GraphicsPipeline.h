#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"
#include "FileReader.h"
#include "Shaders.h"

using namespace Shaders;

class GraphicsPipeline {  
public:
    static void createGraphicsPipeline(Device* device);
    static void createVertexBuffers(Device* device);
};
