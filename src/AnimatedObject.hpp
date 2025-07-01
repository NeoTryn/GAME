#include "GameObject.hpp"

#include <cmath>

#ifndef ANIMATED_OBJECT_HPP
#define ANIMATED_OBJECT_HPP

class AnimatedObject : public GameObject {
protected:

    int steps;
    float animTime;
    bool animDirection = true;

    float time;

public:

    int calculateCurrentStep(float deltaTime);
};

#endif