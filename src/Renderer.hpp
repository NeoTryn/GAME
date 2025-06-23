#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <vector>
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

    unsigned int EBO;

    std::unordered_map<std::string, std::vector<unsigned int>> VAO;
    std::unordered_map<std::string, Texture> textures;

    Shader* shader;

public:

    Renderer(Shader* shader);

    Renderer() = default;
    ~Renderer() = default;

    void loadBatch(std::string name, int column, int row);
    void loadTexture(const char* path, std::string name);

    void render(std::string name, int unit);
    void drawSprite(std::string name, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, int unit);

    std::unordered_map<std::string, std::vector<unsigned int>> getVAO();
    unsigned int getEBO();

    void destroy();
};

#endif