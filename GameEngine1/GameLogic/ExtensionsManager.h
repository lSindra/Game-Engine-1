#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <vector>

class ExtensionsManager {
public:
    std::vector<const char*> getRequiredExtensions();
};
