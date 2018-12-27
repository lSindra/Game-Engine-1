#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"
#include "Shaders.h"

using namespace Shaders;

class DescriptorManager {
public:
    static void create(VkDevice* device, Graphics* graphics);
    static void createDescriptorPool(Device* device);
    static void createDescriptorSets(Device* device);
    static void createDescriptorSetLayout(VkDevice* device, Graphics* graphics);
};
