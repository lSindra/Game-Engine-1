#include "Game.h"

void Game::run() {
    initVulkan();
    mainLoop();
    cleanup();
}

void Game::initVulkan(){
    world_device = std::make_shared<DeviceManager>();
    world_device->initDevice();
}

void Game::mainLoop(){
    while (!glfwWindowShouldClose(world_device->getWindow())) {
        glfwPollEvents();
    }}

void Game::cleanup(){
    world_device->cleanup();
}
