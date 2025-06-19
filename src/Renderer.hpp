#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
private:

    std::vector<unsigned int> VAO, EBO;

public:

    void generate(const float vertices[], int count, int stride, int location);
};

#endif