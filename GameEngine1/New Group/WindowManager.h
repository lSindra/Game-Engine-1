#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Renderer.h"

#include <iostream>

class WindowManager {
private:
    int WIDTH = 800;
    int HEIGHT = 600;
    
    int* width;
    int* height;
    
private:
    WindowManager();
    
public:
    static WindowManager* getInstance();

    GLFWwindow* window;

    void initWindow();
    void destroyWindow();
};
