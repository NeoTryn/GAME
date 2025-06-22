#include <glad/glad.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
private:

    float speed;
    glm::vec2 position;
    glm::vec2 size;

    std::string textureName;
    const char* texturePath;

public:

    Player(glm::vec2 position, glm::vec2 size);
    Player();
    ~Player() = default;

    void move(GLFWwindow* window, float deltaTime);

    glm::vec2 getPosition();
    glm::vec2 getSize();

    std::string getTextureName();
    const char* getTexturePath();
};

#endif