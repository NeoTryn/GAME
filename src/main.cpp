#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {

    // Window hints have to be ABOVE glfwInit() otherwise window creation doesnt work -> CIA is making GLFW do shenanigans now
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit()) {
        std::cout << "CIA wont even let me initialize GLFW!!!!\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "CIA is watching me", NULL, NULL);

    if (!window) {
        std::cout << "CIA has taken my window!!!!...\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "CIA broke OpenGL on my PC....\n";
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, 800, 600);

    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}