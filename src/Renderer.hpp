#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
private:

    unsigned int VAO, EBO;

public:

    Renderer() = default;
    ~Renderer() = default;

    void initialize();

    unsigned int getVAO();
    unsigned int getEBO();

    void destroy();
};

#endif