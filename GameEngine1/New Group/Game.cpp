#include "Game.h"

Game::Game() {
#if BUILD_ENABLE_VULKAN_DEBUG
    std::cout << "Game object created\n";
#endif
}

void Game::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Game::initWindow(){
    world_window = std::make_shared<WindowManager>();
    world_window->initWindow();
}

void Game::initVulkan(){
    
}

void Game::mainLoop(){
    while (!glfwWindowShouldClose(world_window->window)) {
        glfwPollEvents();
    }}

void Game::cleanup(){
    glfwDestroyWindow(world_window->window);
    
    glfwTerminate();
}
