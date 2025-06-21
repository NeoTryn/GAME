#include "Renderer.hpp"

#include <GLFW/glfw3.h>

#ifndef GAME_HPP
#define GAME_HPP

#define FRUSTUM_WIDTH 800.0f
#define FRUSTUM_HEIGHT 600.0f

class Game {
private:

    GLFWwindow* window;

    Shader shader;
    Renderer renderer;

public:

    Game(const char* title, float frustum_width, float frustum_height);

    GLFWwindow* getWindow();
    void setWindow(GLFWwindow* window);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void check_input(GLFWwindow* window);

    void clear();
    void update();
    void render();

    void clean();

    void run();

    Renderer* getRenderer();
};

#endif