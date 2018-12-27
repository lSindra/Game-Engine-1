#include "DescriptorManager.h"

void DescriptorManager::create(VkDevice* logicalDevice, Graphics* graphics) {
    createDescriptorSetLayout(logicalDevice, graphics);
}

static VkDescriptorSetLayoutBinding getUBOLayoutBinding(VkDevice* logicalDevice, Graphics* graphics) {
    VkDescriptorSetLayoutBinding uboLayoutBinding = {};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr;
    
    return uboLayoutBinding;
}

void DescriptorManager::createDescriptorSetLayout(VkDevice* logicalDevice, Graphics* graphics) {
    VkDescriptorSetLayoutBinding uboLayoutBinding = getUBOLayoutBinding(logicalDevice, graphics);
    
    VkDescriptorSetLayoutCreateInfo layoutInfo = {};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;
    
    if (vkCreateDescriptorSetLayout(*logicalDevice, &layoutInfo, nullptr, &graphics->descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

void DescriptorManager::createDescriptorPool(Device* device) {
    VkDescriptorPoolSize poolSize = {};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = static_cast<uint32_t>(device->swapChain.swapChainImages.size());
    
    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = static_cast<uint32_t>(device->swapChain.swapChainImages.size());;
    
    if (vkCreateDescriptorPool(device->logicalDevice, &poolInfo, nullptr, &device->graphics.descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void DescriptorManager::createDescriptorSets(Device *device) {
    std::vector<VkDescriptorSetLayout> layouts(device->swapChain.swapChainImages.size(), device->graphics.descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = device->graphics.descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(device->swapChain.swapChainImages.size());
    allocInfo.pSetLayouts = layouts.data();
    
    device->graphics.descriptorSets.resize(device->swapChain.swapChainImages.size());
    if (vkAllocateDescriptorSets(device->logicalDevice, &allocInfo, device->graphics.descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }
    
    for (size_t i = 0; i < device->swapChain.swapChainImages.size(); i++) {
        VkDescriptorBufferInfo bufferInfo = {};
        bufferInfo.buffer = device->graphics.uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);
        
        VkWriteDescriptorSet descriptorWrite = {};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = device->graphics.descriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;
        descriptorWrite.pImageInfo = nullptr; // Optional
        descriptorWrite.pTexelBufferView = nullptr; // Optional
        
        vkUpdateDescriptorSets(device->logicalDevice, 1, &descriptorWrite, 0, nullptr);
    }
}
