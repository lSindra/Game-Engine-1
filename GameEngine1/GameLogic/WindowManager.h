#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class WindowManager {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    
public:
    GLFWwindow* window;
    VkSurfaceKHR surface;
    
    
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto windowManager = reinterpret_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        windowManager->framebufferResized = true;
    }
    
    bool framebufferResized = false;
    
public:
    void createSurface();
    void initWindow();
};
