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

void GameLogic::Run() {
    initVulkan();
    mainLoop();
    cleanup();
}

void GameLogic::initVulkan() {
    instanceManager.createInstance();
    
    if(validationLayerManager.enableValidationLayers) {
        debugger.setupDebugCallback(instanceManager.instance);
    }
    
    windowManager.initWindow();
    windowManager.createSurface();
    deviceManager.pickPhysicalDevice();
    deviceManager.createLogicalDevice();
    swapChainManager.createSwapChain();
    swapChainManager.createImageViews();
    renderer.createRenderPass();
    shaderGraphics.createGraphicsPipeline();
    renderer.createFramebuffers();
    shaderGraphics.createCommandPool();
    shaderGraphics.createCommandBuffers();
    renderer.createSyncObjects();
}

void GameLogic::mainLoop() {
    while (!glfwWindowShouldClose(windowManager.window)) {
        glfwPollEvents();
        renderer.drawFrame();
    }
    
    vkDeviceWaitIdle(deviceManager.device);
}

void GameLogic::cleanup() {
    VkDevice device = deviceManager.device;
    VkInstance instance = instanceManager.instance;
    swapChainManager.cleanupSwapChain();
    
    renderer.cleanupSemaphores();
    shaderGraphics.cleanup();
    
    vkDestroyDevice(device, nullptr);
    
    if (validationLayerManager.enableValidationLayers) {
        debugger.clearDebugCallback(instance);
    }
    
    vkDestroySurfaceKHR(instance, windowManager.surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    
    glfwDestroyWindow(windowManager.window);
    
    glfwTerminate();
}
