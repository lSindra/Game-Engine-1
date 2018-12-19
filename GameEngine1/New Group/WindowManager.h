#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>

class WindowManager {
private:
    int WIDTH = 800;
    int HEIGH = 600;
    
    int* width;
    int* height;
    
public:
    GLFWwindow* window;

    void initWindow();
    void destroyWindow();
};
