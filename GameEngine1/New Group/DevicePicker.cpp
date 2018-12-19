#include "DevicePicker.h"

const vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

void DevicePicker::pickPhysicalDevice(Device* device) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(device->instance, &deviceCount, nullptr);
    
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(device->instance, &deviceCount, devices.data());
    
    for (const auto& singleDevice : devices) {
        if (isDeviceSuitable(singleDevice, &device->surface)) {
            device->physicalDevice = singleDevice;
            break;
        }
    }
    
    if (device->physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

static bool checkDeviceForSwapChainSupport(Device* device) {
    bool swapChainAdequate = false;
    SwapChainManager::SwapChainSupportDetails swapChainSupport = SwapChainManager::querySwapChainSupport(device);
    swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    return swapChainAdequate;
}

bool DevicePicker::isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR* surface) {
    Device* tempDevice = new Device();
    tempDevice->physicalDevice = physicalDevice;
    tempDevice->surface = *surface;

    return QueueFamiliesManager::findQueueFamilies(tempDevice).isComplete() &&
            checkDeviceExtensionSupport(tempDevice) &&
            checkDeviceForSwapChainSupport(tempDevice);
}

bool DevicePicker::checkDeviceExtensionSupport(Device* device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device->physicalDevice, nullptr, &extensionCount, nullptr);
    
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device->physicalDevice, nullptr, &extensionCount, availableExtensions.data());
    
    std::set<std::string> requiredExtensions(device->deviceExtensions.begin(), device->deviceExtensions.end());
    
    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }
    
    return requiredExtensions.empty();
}

void DevicePicker::createLogicalDevice(Device* device) {
    ValidationLayersManager validationLayersManager = ValidationLayersManager::getInstance();
    QueueFamilyIndices indices = QueueFamiliesManager::findQueueFamilies(device);
    vector<VkDeviceQueueCreateInfo> queueCreateInfos = QueueFamiliesManager::getQueueInfos(indices);
    
    VkPhysicalDeviceFeatures deviceFeatures = {};
    
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(device->deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = device->deviceExtensions.data();
    
    if (validationLayersManager.isValidationLayersEnabled()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    
    if (vkCreateDevice(device->physicalDevice, &createInfo, nullptr, &device->logicalDevice) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    
    vkGetDeviceQueue(device->logicalDevice, indices.graphicsFamily.value(), 0, &device->graphicsQueue);
    vkGetDeviceQueue(device->logicalDevice, indices.presentFamily.value(), 0, &device->presentQueue);
}

void DevicePicker::createSwapChain(Device* device) {
    SwapChainManager::SwapChainSupportDetails swapChainSupport = SwapChainManager::querySwapChainSupport(device);
    
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
