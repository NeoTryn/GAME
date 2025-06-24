#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

class GameObject {
protected:

    glm::vec2 position, size;

    std::string name;
    const char* texturePath;
    
    int column, row;

public:
};

#endif