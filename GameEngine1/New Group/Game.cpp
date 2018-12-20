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
    while (!glfwWindowShouldClose(world_device->getWindow())) {
        glfwPollEvents();
        renderer.drawFrame(world_device->getDevice());
    }}

void Game::cleanup(){
    renderer.cleanup(world_device->getDevice());
    world_device->cleanup();
}
