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

    Game::shader = {"../src/shaders/vertex_shader_1.glsl", "../src/shaders/fragment_shader_1.glsl"};

    Game::renderer = {};
    Game::renderer.initialize();
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

Renderer* Game::getRenderer() {
    return &renderer;
}

void Game::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::render() {
    shader.use();
    glBindVertexArray(Game::renderer.getVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::renderer.getEBO());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Game::update() {
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(400.0f, 300.0f, 0.0f));

    model = glm::scale(model, glm::vec3(500.0f));
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    shader.uniformMat4("model", model);
    shader.uniformMat4("proj", projection);
}

void Game::clean() {

    Game::renderer.destroy();
    Game::shader.destroy();

    glfwDestroyWindow(Game::window);
    glfwTerminate();
}

void Game::run() {
    while (!glfwWindowShouldClose(Game::window)) {
        Game::check_input(Game::window);

        Game::clear();
        Game::update();
        Game::render();

        glfwSwapBuffers(Game::window);
        glfwPollEvents();
    }

    Game::clean();
}