#include "Renderer.hpp"

Renderer::Renderer(Shader* shader) {
    Renderer::shader = shader;
}

void Renderer::loadBatch(std::string name, int column, int row) {
    
    std::vector<unsigned int> VAOs;

    const unsigned int indices[] = {
        0, 1, 2,
        2, 1, 3
    };

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer::EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    for (int i = 0; i < column; i++) {
            for (int j = 0; j < row; j++) {

            float oneColumn = static_cast<float>(1) / static_cast<float>(column);
            float oneRow = static_cast<float>(1) / static_cast<float>(row);

            //std::cout << oneRow << "\n";

            float startColumn = static_cast<float>(oneColumn * i);
            float endColumn = static_cast<float>(oneColumn * i) + oneColumn;

            float startRow = static_cast<float>(oneRow * j);
            float endRow = static_cast<float>(oneRow * j) + oneRow;

            //std::cout << startRow << "\n";
            //std::cout << endRow << "\n";
            
            //std::cout << j << "\n";

            const float vertices[] = {
                -1.0f,  1.0f, 0.0f, startColumn,  endRow,
                -1.0f, -1.0f, 0.0f, startColumn,  startRow,
                 1.0f,  1.0f, 0.0f, endColumn  ,  endRow,
                 1.0f, -1.0f, 0.0f, endColumn  ,  startRow
            };

            unsigned int VBO, VAO;

            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindVertexArray(0);

            glBindBuffer(GL_VERTEX_ARRAY, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glDeleteBuffers(1, &VBO);

            VAOs.push_back(VAO);
        }
    }

    Renderer::VAO[name] = VAOs;
}

void Renderer::loadTexture(const char* path, std::string name) {

    unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);

    Texture newTexture = {width, height, nrChannels, texture};
    Renderer::textures[name] = newTexture;

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawSprite(std::string name, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, int unit) {
    Renderer::shader->use();
    Renderer::shader->uniformInt("image", unit);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 0.0f));

    Renderer::shader->uniformMat4("model", model);
    Renderer::shader->uniformVec3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0 + unit);

    //std::cout << Renderer::textures[name].nrChannels << "\n";

    glBindTexture(GL_TEXTURE_2D, Renderer::textures[name].texture);
}

void Renderer::renderStaticObject(std::string name, GameObject* object) {
    Renderer::shader->use();

    // 4 seconds and 4 animation steps. if its 2 different numbers you have to calculate how long a step takes. steps = rows * columns.
    // oneStepTime = animTime / animSteps. currentStep = static_cast<int>(currentTime / oneStepTime) 
    
    glBindVertexArray(Renderer::VAO[name][0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer::EBO);
}

void Renderer::renderAnimatedObject(std::string name, AnimatedObject* object) {
    Renderer::shader->use();

    // 4 seconds and 4 animation steps. if its 2 different numbers you have to calculate how long a step takes. steps = rows * columns.
    // oneStepTime = animTime / animSteps. currentStep = static_cast<int>(currentTime / oneStepTime) 
    int currentStep = object->calculateCurrentStep();
    glBindVertexArray(Renderer::VAO[name][currentStep]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer::EBO);
}

std::unordered_map<std::string, std::vector<unsigned int>> Renderer::getVAO() {
    return Renderer::VAO;
}

unsigned int Renderer::getEBO() {
    return Renderer::EBO;
}

void Renderer::destroy() {
    glDeleteBuffers(1, &EBO);

    for (const auto& pair : Renderer::VAO) {
        std::vector<unsigned int> VAOs = pair.second;
        glDeleteVertexArrays(pair.second.size(), VAOs.data());
    }
}

Texture::Texture(int width, int height, int nrChannels, unsigned int texture) {
    Texture::width = width;
    Texture::height = height;
    Texture::nrChannels = nrChannels;

    Texture::texture = texture;
}