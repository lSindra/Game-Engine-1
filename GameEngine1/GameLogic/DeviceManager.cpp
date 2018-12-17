#include "DeviceManager.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "FileReader.h"
#include "GameLogic.h"
#include "SwapChainManager.h"
#include "WindowManager.h"
#include "Renderer.h"

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

void DeviceManager::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instanceManager.instance, &deviceCount, nullptr);
    
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instanceManager.instance, &deviceCount, devices.data());
    
    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }
    
    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void DeviceManager::createLogicalDevice() {
    QueueFamiliesManager::QueueFamilyIndices indices = queueFamiliesManager.findQueueFamilies(physicalDevice, windowManager.surface);
    
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
    
    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }
    
    VkPhysicalDeviceFeatures deviceFeatures = {};
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    
    createInfo.pEnabledFeatures = &deviceFeatures;
    
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    
    if (validationLayerManager.enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayerManager.validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayerManager.validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    
    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    
    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &queueFamiliesManager.graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &queueFamiliesManager.presentQueue);
}

bool DeviceManager::isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamiliesManager::QueueFamilyIndices indices = queueFamiliesManager.findQueueFamilies(device, windowManager.surface);
    
    bool extensionsSupported = checkDeviceExtensionSupport(device);
    
    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = swapChainManager.querySwapChainSupport();
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }
    
    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool DeviceManager::checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
    
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
    
    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
    
    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }
    
    return requiredExtensions.empty();
}
