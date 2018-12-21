#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Device.h"
#include "QueueFamiliesManager.h"
#include "GraphicsPipeline.h"
#include "WindowManager.h"

#include <vector>

using namespace QueueFamilies;
using namespace std;

class SwapChainManager {
public:
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        vector<VkSurfaceFormatKHR> formats;
        vector<VkPresentModeKHR> presentModes;
    };
    
public:
    static void createSwapChain(Device* device);
    static void recreateSwapChain(Device* device);
    static SwapChainSupportDetails querySwapChainSupport(Device* device);
    static void cleanup(Device* device);
    
private:
    static void initSwapChain(Device* device);
    static void createImageViews(Device* device);
    static void createRenderPass(Device* device);
    static void createCommandPool(Device* device);
    static void createCommandBuffers(Device* device);
    static void createFrameBuffers(Device* device);
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
    static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, Device* device);
};
