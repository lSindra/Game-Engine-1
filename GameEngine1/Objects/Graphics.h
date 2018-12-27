#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

using namespace std;

struct Graphics {
    VkPipeline graphicsPipeline;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkBuffer vertexBuffer;
    VkBuffer indexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkDeviceMemory indexBufferMemory;
    VkCommandPool commandPool;
    VkDescriptorPool descriptorPool;
    vector<VkDescriptorSet> descriptorSets;
    vector<VkCommandBuffer> commandBuffers;
    vector<VkBuffer> uniformBuffers;
    vector<VkDeviceMemory> uniformBuffersMemory;
};
