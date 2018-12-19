#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"
#include "FileReader.h"

class GraphicsPipeline {  
public:
    static void createGraphicsPipeline(Device* device);
};
