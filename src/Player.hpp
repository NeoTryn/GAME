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

    float speed = 100.0f;
    glm::vec2 position;
    glm::vec2 size;

    std::string name = "player";
    const char* texturePath = "../img/squid.png";

    int count = 4;
    float animTimeSeconds = 4.0f;

public:

    Player(glm::vec2 position, glm::vec2 size);
    Player();
    ~Player() = default;

    void move(GLFWwindow* window, float deltaTime);

    glm::vec2 getPosition();
    glm::vec2 getSize();

    std::string getName();
    const char* getTexturePath();
    int getCount();
    float getAnimTimeSeconds();
};

#endif