#include "Player.hpp"

Player::Player(glm::vec2 position) {
    Player::position = position;
    Player::speed = 60.0f;
    Player::textureName = "face";
}

Player::Player() {
    Player::position = glm::vec2(300.0f, 400.0f);
    Player::speed = 60.0f;
    Player::textureName = "face";
}

glm::vec2 Player::getPosition() {
    return Player::position; 
}

std::string Player::getTextureName() {
    return Player::textureName;
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