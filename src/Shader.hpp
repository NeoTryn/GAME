#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
private:

    unsigned int program;

public:

    Shader(const char* vertPath, const char* fragPath);

    std::string readFile(const char* path);

    void checkShaderCompilation(unsigned int shader);
    void checkProgramLinking(unsigned int program);

    void use();

    void uniformInt(std::string location, int value);
    void uniformFloat(std::string location, float value);
    void uniformBool(std::string location, bool value);

    void uniformVec2(std::string location);
};

#endif