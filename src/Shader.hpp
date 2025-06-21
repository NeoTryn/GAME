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
    Shader() = default;
    ~Shader() = default;
 
    unsigned int getProgram();
    void setProgram(unsigned int program);

    std::string readFile(const char* path);

    void checkShaderCompilation(unsigned int shader);
    void checkProgramLinking(unsigned int program);

    void use();

    void uniformInt(const char* name, int value);
    void uniformFloat(const char* name, float value);
    void uniformBool(const char* name, bool value);

    void uniformVec2(const char* name, glm::vec2 value);
    void uniformVec3(const char* name, glm::vec3 value);
    void uniformVec4(const char* name, glm::vec4 value);

    void uniformMat2(const char* name, glm::mat2 value);
    void uniformMat3(const char* name, glm::mat3 value);
    void uniformMat4(const char* name, glm::mat4 value);

    void destroy();
};

#endif