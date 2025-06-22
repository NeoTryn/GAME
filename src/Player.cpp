#include "Player.hpp"

Player::Player(glm::vec2 position, glm::vec2 size) {
    Player::position = position;
    Player::size = size;
    Player::speed = 100.0f;
    Player::textureName = "face";
    Player::texturePath = "../img/awesomeface.png";
}

Player::Player() {
    Player::position = glm::vec2(400.0f, 300.0f);
    Player::size = glm::vec2(400.0f, 300.0f);
    Player::speed = 100.0f;
    Player::textureName = "face";
    Player::texturePath = "../img/awesomeface.png";
}

glm::vec2 Player::getPosition() {
    return Player::position; 
}

glm::vec2 Player::getSize() {
    return Player::size;
}

std::string Player::getTextureName() {
    return Player::textureName;
}

const char* Player::getTexturePath() {
    return Player::texturePath;
}

void Player::move(GLFWwindow* window, float deltaTime) {
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
}