#include "Game.h"

void Game::run() {
    initVulkan();
    mainLoop();
    cleanup();
}

void Game::initVulkan(){
    world_device = std::make_shared<DeviceManager>();
    world_device->initDevice();
    renderer.createSemaphores(world_device->getDevice());
}

void Game::mainLoop(){
    while (!glfwWindowShouldClose(WindowManager::getInstance()->window)) {
        glfwPollEvents();
        renderer.drawFrame(world_device->getDevice());
    }
    vkDeviceWaitIdle(world_device->getDevice()->logicalDevice);
}

void Game::cleanup(){
    world_device->cleanupSwapChain();
    renderer.cleanup(world_device->getDevice());
    world_device->cleanup();
}
