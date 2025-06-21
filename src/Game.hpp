#include "Shader.hpp"
#include "Renderer.hpp"

#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#ifndef GAME_HPP
#define GAME_HPP

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