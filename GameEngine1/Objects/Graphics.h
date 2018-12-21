#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

using namespace std;

struct Graphics {
    VkPipeline graphicsPipeline;
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkCommandPool commandPool;
    vector<VkCommandBuffer> commandBuffers;
};
