#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "FileReader.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

class ValidationLayerManager {
#ifdef NDEBUG
public:
    const bool enableValidationLayers = false;
#else
public:
    const bool enableValidationLayers = true;
#endif
    
public:
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };
    
public:
    bool checkValidationLayerSupport();
};
