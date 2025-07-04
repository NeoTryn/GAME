#include "Renderer.hpp"
#include "Player.hpp"

#include <GLFW/glfw3.h>

#ifndef GAME_HPP
#define GAME_HPP

#define FRUSTUM_WIDTH 160.0f
#define FRUSTUM_HEIGHT 90.0f

class Game {
private:

    GLFWwindow* window;

    Shader shader;
    Renderer renderer;
    Player player;

    float lastTime, currentTime, deltaTime;

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