#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "FileReader.h"
#include "GameLogic.h"
#include "SwapChainManager.h"
#include "WindowManager.h"
#include "Renderer.h"
#include "ValidationLayerManager.h"
#include "DeviceManager.h"
#include "InstanceManager.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

using namespace Game;

void InstanceManager::createInstance() {
    if (validationLayerManager.enableValidationLayers && !validationLayerManager.checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    auto extensions = extensionsManager.getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    
    if (validationLayerManager.enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayerManager.validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayerManager.validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

