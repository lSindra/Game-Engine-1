#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

class ValidationLayersManager {
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
    
    const vector<const char*> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };
    
    VkDebugUtilsMessengerEXT callback;
    VkInstance instance;
    
public:
    static ValidationLayersManager* getInstance();
    
private:
    VkResult createDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);
    void destroyDebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
    void initValidationLayers();
    ValidationLayersManager();
    
public:
    bool isValidationLayersEnabled();
    bool checkValidationLayerSupport();
    vector<const char*> getValidationLayers();
    void cleanup();
    void setupDebugCallback(VkInstance instance);
};
