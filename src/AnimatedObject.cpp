#include "AnimatedObject.hpp"

int AnimatedObject::calculateCurrentStep() {
    return static_cast<int>(AnimatedObject::time / (AnimatedObject::animTime / AnimatedObject::steps));
}