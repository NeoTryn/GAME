#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <iostream>

#include "stb_image.h"

#include "Shader.hpp"

#ifndef RENDERER_HPP
#define RENDERER_HPP

struct Texture{
    int width, height, nrChannels;
    unsigned int texture;

    Texture(int width, int height, int nrChannels, unsigned int texture);
    Texture() = default;
    ~Texture() = default;
};

class Renderer {
private:

    unsigned int VAO, EBO;

    std::unordered_map<std::string, Texture> textures;

    Shader* shader;

public:

    Renderer(Shader* shader);

    Renderer() = default;
    ~Renderer() = default;

    void initialize();

    void loadTexture(const char* path, std::string name);

    void render();
    void drawSprite(std::string name, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, int unit);

    unsigned int getVAO();
    unsigned int getEBO();

    void destroy();
};

#endif