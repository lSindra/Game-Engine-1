#include "WindowManager.h"

void WindowManager::initWindow() {
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    window = glfwCreateWindow(WIDTH, HEIGH, "Vulkan", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
//        exit(EXIT_FAILURE);
    }
}

void WindowManager::destroyWindow() {
    glfwDestroyWindow(window);
    
    glfwTerminate();
}
