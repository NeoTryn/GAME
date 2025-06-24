#include "GameObject.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player : GameObject {
private:

    float speed = 100.0f;
    bool isMoving = false;

    float animTimeSeconds = 1.0f;
    float currentTime = 0.0f;

    bool animDirection = true;
public:

    Player(glm::vec2 position, glm::vec2 size);
    Player();
    ~Player() = default;

    void move(GLFWwindow* window, float deltaTime);

    glm::vec2 getPosition();
    glm::vec2 getSize();

    const std::string& getName();
    const char* getTexturePath();

    const int& getColumn();
    const int& getRow();

    const float& getAnimTimeSeconds();
    const float& getCurrentTimeSeconds();

    const bool& getIsMoving();
    const bool& getAnimDirection();

    void setCurrentTimeSeconds(const float& currentTime);
    void setIsMoving(const bool& isMoving);
    void setAnimDirection(const bool& animDirection);
};

#endif