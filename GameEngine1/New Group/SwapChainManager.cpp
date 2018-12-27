#include "SwapChainManager.h"

void SwapChainManager::initSwapChain(Device* device) {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
    
    VkSurfaceFormatKHR surfaceFormat = SwapChainManager::chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = SwapChainManager::chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = SwapChainManager::chooseSwapExtent(swapChainSupport.capabilities, device);
    
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }
    
    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = device->surface;
    
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    
    QueueFamilyIndices indices = QueueFamilies::QueueFamiliesManager::findQueueFamilies(device);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
    
    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }
    
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    
    if (vkCreateSwapchainKHR(device->logicalDevice, &createInfo, nullptr, &device->swapChain.swapChainKHR) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }
    
    vkGetSwapchainImagesKHR(device->logicalDevice, device->swapChain.swapChainKHR, &imageCount, nullptr);
    device->swapChain.swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device->logicalDevice, device->swapChain.swapChainKHR, &imageCount, device->swapChain.swapChainImages.data());
    
    device->swapChain.swapChainImageFormat = surfaceFormat.format;
    device->swapChain.swapChainExtent = extent;
}


void SwapChainManager::createSwapChain(Device *device) {
    initSwapChain(device);
    createImageViews(device);
    createRenderPass(device);
    DescriptorManager::create(&device->logicalDevice, &device->graphics);
    GraphicsPipeline::create(device);
}

void SwapChainManager::recreateSwapChain(Device *device) {
    int width = 0, height = 0;
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(WindowManager::getInstance()->window, &width, &height);
        glfwWaitEvents();
    }
    
    vkDeviceWaitIdle(device->logicalDevice);
    
    cleanup(device);
    
    createSwapChain(device);
}

SwapChainManager::SwapChainSupportDetails SwapChainManager::querySwapChainSupport(Device* device) {
    SwapChainSupportDetails details;
    
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physicalDevice, device->surface, &details.capabilities);
    
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device->physicalDevice, device->surface, &formatCount, nullptr);
    
    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device->physicalDevice, device->surface, &formatCount, details.formats.data());
    }
    
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device->physicalDevice, device->surface, &presentModeCount, nullptr);
    
    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device->physicalDevice, device->surface, &presentModeCount, details.presentModes.data());
    }
    
    return details;
}

VkSurfaceFormatKHR SwapChainManager::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }
    
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }
    
    return availableFormats[0];
}

VkPresentModeKHR SwapChainManager::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes) {
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;
    
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        } else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            bestMode = availablePresentMode;
        }
    }
    
    return bestMode;
}

VkExtent2D SwapChainManager::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, Device* device) {
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(WindowManager::getInstance()->window, &width, &height);
        
        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };
        return actualExtent;
    }
}

void SwapChainManager::createImageViews(Device *device) {
    device->swapChain.swapChainImageViews.resize(device->swapChain.swapChainImages.size());
    
    for (size_t i = 0; i < device->swapChain.swapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = device->swapChain.swapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = device->swapChain.swapChainImageFormat;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
        
        if (vkCreateImageView(device->logicalDevice, &createInfo, nullptr, &device->swapChain.swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }
}

void SwapChainManager::createRenderPass(Device *device) {
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = device->swapChain.swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    
    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    
    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    
    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    
    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;
    
    if (vkCreateRenderPass(device->logicalDevice, &renderPassInfo, nullptr, &device->graphics.renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }
}

void SwapChainManager::cleanup(Device* device) {
    for (size_t i = 0; i < device->swapChain.swapChainFramebuffers.size(); i++) {
        vkDestroyFramebuffer(device->logicalDevice, device->swapChain.swapChainFramebuffers[i], nullptr);
    }
    
    vkFreeCommandBuffers(device->logicalDevice, device->graphics.commandPool, static_cast<uint32_t>(device->graphics.commandBuffers.size()), device->graphics.commandBuffers.data());

    vkDestroyDescriptorPool(device->logicalDevice, device->graphics.descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(device->logicalDevice, device->graphics.descriptorSetLayout, nullptr);

    for (size_t i = 0; i < device->swapChain.swapChainImages.size(); i++) {
        vkDestroyBuffer(device->logicalDevice, device->graphics.uniformBuffers[i], nullptr);
        vkFreeMemory(device->logicalDevice, device->graphics.uniformBuffersMemory[i], nullptr);
    }
    
    vkDestroyPipeline(device->logicalDevice, device->graphics.graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device->logicalDevice, device->graphics.pipelineLayout, nullptr);
    vkDestroyRenderPass(device->logicalDevice, device->graphics.renderPass, nullptr);
    
    for (size_t i = 0; i < device->swapChain.swapChainImageViews.size(); i++) {
        vkDestroyImageView(device->logicalDevice, device->swapChain.swapChainImageViews[i], nullptr);
    }
    
    vkDestroySwapchainKHR(device->logicalDevice, device->swapChain.swapChainKHR, nullptr);
}
