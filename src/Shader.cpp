#include "Shader.hpp"

Shader::Shader(const char* vertPath, const char* fragPath) {
    std::string vertexString = readFile(vertPath);
    std::string fragmentString = readFile(fragPath);

    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    unsigned int vertexShader, fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);

    Shader::checkShaderCompilation(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);

    Shader::checkShaderCompilation(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program); 

    Shader::checkProgramLinking(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int Shader::getProgram() {
    return Shader::program;
}

void Shader::setProgram(unsigned int program) {
    Shader::program = program;
} 

std::string Shader::readFile(const char* path) {
    try {
        std::string line, text;

        std::ifstream stream(path);

        while (getline(stream, line)) {
            text += line;
            text += "\n";
        }

        return text;
    }
    catch(std::exception error) {
        std::cout << "CIA deleted the file...\n";
        return "";
    }
}

void Shader::checkShaderCompilation(unsigned int shader) {
    int success, type;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        glGetShaderiv(shader, GL_SHADER_TYPE, &type);

        if (type == GL_VERTEX_SHADER) {
            std::cout << "Vertex Shader ";
        }
        // Maybe a third type of shader in the end?
        else if (type == GL_FRAGMENT_SHADER) {
            std::cout << "Fragment Shader ";
        }

        std::cout << "compilation failed.\n Log: " << infoLog;
    }
}

void Shader::checkProgramLinking(unsigned int program) {
    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);

        std::cout << "Shader Program compilation failed.\n Log: " << infoLog;
    }
}

void Shader::use() {
    glUseProgram(Shader::program);
}

void Shader::uniformInt(const char* name, int value) {
    glUniform1i(glGetUniformLocation(Shader::program, name), value);
}

void Shader::uniformFloat(const char* name, float value) {
    glUniform1f(glGetUniformLocation(Shader::program, name), value);
}

void Shader::uniformBool(const char* name, bool value) {
    glUniform1i(glGetUniformLocation(Shader::program, name), static_cast<int>(value));
}

void Shader::uniformVec2(const char* name, glm::vec2 value) {
    glUniform2fv(glGetUniformLocation(Shader::program, name), 1, glm::value_ptr(value));
}

void Shader::uniformVec3(const char* name, glm::vec3 value) {
    glUniform3fv(glGetUniformLocation(Shader::program, name), 1, glm::value_ptr(value));
}

void Shader::uniformVec4(const char* name, glm::vec4 value) {
    glUniform4fv(glGetUniformLocation(Shader::program, name), 1, glm::value_ptr(value));
}

void Shader::uniformMat2(const char* name, glm::mat2 value) {
    glUniformMatrix2fv(glGetUniformLocation(Shader::program, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::uniformMat3(const char* name, glm::mat3 value) {
    glUniformMatrix3fv(glGetUniformLocation(Shader::program, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::uniformMat4(const char* name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(Shader::program, name), 1, GL_FALSE, glm::value_ptr(value));
}