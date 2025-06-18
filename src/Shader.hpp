#include <iostream>
#include <fstream>
#include <string>

#include "glad.h"

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
};

#endif