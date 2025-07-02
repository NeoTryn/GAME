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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    Game::shader = {"../src/shaders/vertex_shader_1.glsl", "../src/shaders/fragment_shader_1.glsl"};

    Game::player = {glm::vec2(100.0f, 50.0f), glm::vec2(10.0f, 10.0f)};

    Game::renderer = {&shader};
    Game::renderer.loadBatch(Game::player.getName(), Game::player.getColumn(), Game::player.getRow());

    Game::renderer.loadTexture(Game::player.getTexturePath(), Game::player.getName());

    Game::lastTime = static_cast<float>(glfwGetTime());

    //std::cout << Game::player.getAnimTimeSeconds() << "\n";
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
    Game::renderer.renderAnimatedObject(Game::player.getName(),&player, Game::deltaTime);
}

void Game::update() {
    Game::currentTime = static_cast<float>(glfwGetTime());

    Game::deltaTime = Game::currentTime - Game::lastTime;
    
    Game::lastTime = Game::currentTime;

    /*if (Game::player.getCurrentTimeSeconds() <= Game::player.getAnimTimeSeconds() && Game::player.getAnimDirection()) {
        Game::player.setCurrentTimeSeconds(Game::player.getCurrentTimeSeconds() + Game::deltaTime);
    }
    else if (Game::player.getCurrentTimeSeconds() >= 0.0f && !Game::player.getAnimDirection()){
        Game::player.setCurrentTimeSeconds(Game::player.getCurrentTimeSeconds() - Game::deltaTime);
    }
    else if (Game::player.getCurrentTimeSeconds() <= Game::player.getAnimTimeSeconds()) {
        Game::player.setAnimDirection(true);
        Game::player.setCurrentTimeSeconds(Game::player.getCurrentTimeSeconds() + Game::deltaTime);
    }
    else if (Game::player.getCurrentTimeSeconds() >= 0.0f) {
        Game::player.setAnimDirection(false);
        Game::player.setCurrentTimeSeconds(Game::player.getCurrentTimeSeconds() - Game::deltaTime);
    }*/

    // 4 seconds and 4 animation steps. if its 2 different numbers you have to calculate how long a step takes. steps = rows * columns.
    // oneStepTime = animTime / animSteps. currentStep = static_cast<int>(currentTime / oneStepTime) 
    
    // enabling player movement
    Game::player.move(Game::window, Game::deltaTime);

    // drawing the player
    Game::renderer.drawSprite(Game::player.getName(), Game::player.getPosition(), Game::player.getSize(), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), 0);

    shader.use();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, FRUSTUM_WIDTH, FRUSTUM_HEIGHT, 0.0f, -1.0f, 1.0f);

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