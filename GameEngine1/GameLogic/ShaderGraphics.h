#pragma once

class ShaderGraphics {
public:
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createGraphicsPipeline();
    void freeCommandBuffers();
    void cleanup();
    void createCommandPool();
    void createCommandBuffers();
};
