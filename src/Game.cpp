#include "Game.hpp"

Game::Game(const char* title, float frustum_width, float frustum_height) {

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit()) {
        std::cout << "CIA wont even let me initialize GLFW!!!!\n";
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    Game::window = glfwCreateWindow(mode->width, mode->height, title, glfwGetPrimaryMonitor(), NULL);

    if (!Game::window) {
        std::cout << "CIA has taken my window!!!!...\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(Game::window);
    glfwSetFramebufferSizeCallback(Game::window, Game::framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "CIA broke OpenGL on my PC....\n";
        glfwTerminate();
    }

    glViewport(0, 0, frustum_width, frustum_height);
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
}

GLFWwindow* Game::getWindow() {
    return Game::window;
}

void Game::setWindow(GLFWwindow* window) {
    Game::window = window;
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::check_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}