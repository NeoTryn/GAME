#include <iostream>

#include "Game.hpp"

#include <GLFW/glfw3.h>

int main() {

    Game game = {"CIA is watching me...", 800.0f, 600.0f};

    Shader shader = {"../src/shaders/vertex_shader_1.glsl", "../src/shaders/fragment_shader_1.glsl"};

    shader.use();

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(400.0f, 300.0f, 0.0f));

    model = glm::scale(model, glm::vec3(500.0f));
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    shader.uniformMat4("model", model);
    shader.uniformMat4("proj", projection);

    std::cout << game.getRenderer()->getEBO();

   
    while (!glfwWindowShouldClose(game.getWindow())) {
        game.check_input(game.getWindow());
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shaderProgram);
        shader.use();
        glBindVertexArray(game.getRenderer()->getVAO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game.getRenderer()->getEBO());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(game.getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}