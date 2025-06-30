#include "AnimatedObject.hpp"

int AnimatedObject::calculateCurrentStep() {

    float animTime = AnimatedObject::animTime - 0.5f;
    float time = AnimatedObject::time;

    if (AnimatedObject::time < 0.5f) {

    }

    int currentStep = static_cast<int>(AnimatedObject::time / (animTime / AnimatedObject::steps));

    if (currentStep >= AnimatedObject::steps) {
        currentStep--;
    }

    float result = (AnimatedObject::time / (AnimatedObject::animTime / AnimatedObject::steps));

    std::cout << "Current Step: " << currentStep << " Calculation Result: " << result << " Time: " << AnimatedObject::time << "\n";

    return currentStep;
}