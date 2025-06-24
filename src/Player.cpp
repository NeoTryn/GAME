#include "Player.hpp"

Player::Player(glm::vec2 position, glm::vec2 size) {
    Player::position = position;
    Player::size = size;

    Player::name = "player";
    Player::texturePath = "../img/squid.png";

    Player::column = 4;
    Player::row = 1;
}

Player::Player() {
    Player::position = glm::vec2(400.0f, 300.0f);
    Player::size = glm::vec2(400.0f, 300.0f);

    Player::name = "player";
    Player::texturePath = "../img/squid.png";

    Player::column = 4;
    Player::row = 1;
}

glm::vec2 Player::getPosition() {
    return Player::position; 
}

glm::vec2 Player::getSize() {
    return Player::size;
}

const std::string& Player::getName() {
    return Player::name;
}

const char* Player::getTexturePath() {
    return Player::texturePath;
}

const int& Player::getColumn() {
    return Player::column;
}

const int& Player::getRow() {
    return Player::row;
}

const float& Player::getAnimTimeSeconds() {
    return Player::animTimeSeconds;
}

const float& Player::getCurrentTimeSeconds() {
    return Player::currentTime;
}

const bool& Player::getIsMoving() {
    return Player::isMoving;
}

const bool& Player::getAnimDirection() {
    return Player::animDirection;
}

void Player::setAnimDirection(const bool& animDirection) {
    Player::animDirection = animDirection;
}

void Player::setCurrentTimeSeconds(const float& currentTime) {
    Player::currentTime = currentTime;
}

void Player::setIsMoving(const bool& isMoving) {
    Player::isMoving = isMoving;
}

void Player::move(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            Player::position.y -= speed * deltaTime;
        }   
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            Player::position.y += speed * deltaTime;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            Player::position.x += speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            Player::position.x -= speed * deltaTime;
        }

        Player::isMoving = true;
    }
    else {
        Player::isMoving = false;
    }
}