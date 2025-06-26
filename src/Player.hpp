#include "AnimatedObject.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player : public AnimatedObject {
private:

    float speed = 100.0f;
    bool isMoving = false;

public:

    Player(glm::vec2 position, glm::vec2 size);
    Player();

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

    void setCurrentTimeSeconds(const float& time);
    void setIsMoving(const bool& isMoving);
    void setAnimDirection(const bool& animDirection);
};

#endif