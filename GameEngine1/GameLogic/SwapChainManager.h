#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "FileReader.h"
#include "WindowManager.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class SwapChainManager {
public:
    VkFormat swapChainImageFormat;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    uint32_t getSwapChainImageCount(const SwapChainSupportDetails &swapChainSupport);
    
public:
    SwapChainSupportDetails querySwapChainSupport();
    uint32_t extracted(const SwapChainSupportDetails &swapChainSupport);
    void recreateSwapChain();
    void createImageViews();
    void createSwapChain();
    void cleanupSwapChain();
};
