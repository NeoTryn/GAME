#include "Renderer.hpp"

void Renderer::generate(const float vertices[], int count, int stride, int location) {
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, count * sizeof(float), (void*)(stride * sizeof(float)));
    glEnableVertexAttribArray(location);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);

    Renderer::VAO.push_back(VAO);
}