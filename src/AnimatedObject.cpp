#include "AnimatedObject.hpp"

int AnimatedObject::calculateCurrentStep(float deltaTime) {

    if (AnimatedObject::time >= AnimatedObject::animTime) {
        AnimatedObject::time = 0.0f;
    }
    else {
        AnimatedObject::time += deltaTime;
    }

    float result = std::round((AnimatedObject::time / (AnimatedObject::animTime / AnimatedObject::steps)));

    if (static_cast<int>(result) >= AnimatedObject::steps) {
        result = 0.0f;
    }

    return static_cast<int>(result);
}