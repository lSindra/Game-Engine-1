#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

using namespace std;

struct SwapChain {
    VkSwapchainKHR swapChainKHR;
    vector<VkFramebuffer> swapChainFramebuffers;
    vector<VkImageView> swapChainImageViews;
    vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
};

