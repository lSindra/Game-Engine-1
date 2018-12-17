#pragma once

class Renderer {
    const int MAX_FRAMES_IN_FLIGHT = 2;
    
    std::vector<VkFence> inFlightFences;
    size_t currentFrame = 0;
    
public:
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    
public:
    void createSyncObjects();
    void createRenderPass();
    void drawFrame();
    void createFramebuffers();
    void cleanupPipeline();
    void cleanupSemaphores();
};
