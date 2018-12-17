#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "FileReader.h"
#include "SwapChainManager.h"
#include "Renderer.h"
#include "QueueFamiliesManager.h"
#include "ValidationLayerManager.h"
#include "DebugMessager.h"
#include "WindowManager.h"
#include "DeviceManager.h"
#include "ShaderGraphics.h"
#include "InstanceManager.h"
#include "ExtensionsManager.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <set>

namespace Game {
    SwapChainManager swapChainManager =* new SwapChainManager();
    Renderer renderer =* new Renderer();
    QueueFamiliesManager queueFamiliesManager =* new QueueFamiliesManager();
    ValidationLayerManager validationLayerManager =* new ValidationLayerManager();
    Debugger debugger =* new Debugger();
    WindowManager windowManager =* new WindowManager();
    DeviceManager deviceManager =* new DeviceManager();
    ShaderGraphics shaderGraphics =* new ShaderGraphics();
    InstanceManager instanceManager =* new InstanceManager();
    ExtensionsManager extensionsManager =* new ExtensionsManager();
    
    class GameLogic
    {
    public:
        void Run();
        
    private:
        void initVulkan();
        void mainLoop();
        void cleanup();
    };
}
