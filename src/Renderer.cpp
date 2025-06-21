#include "Renderer.hpp"

Renderer::Renderer(Shader* shader) {
    Renderer::shader = shader;
}

void Renderer::initialize() {
    
    const float vertices[] = {
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f
    };

    const unsigned int indices[] = {
         0, 1, 2,
         0, 1, 3 
    };
    
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO); 
}

void Renderer::loadTexture(const char* path, std::string name, int unit) {

    unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

    Renderer::shader->use();
    Renderer::shader->uniformInt("image", unit);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawSprite(std::string name, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, int unit) {
    Renderer::shader->use();

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

void Renderer::render() {
    Renderer::shader->use();

    glBindVertexArray(Renderer::VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer::EBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int Renderer::getVAO() {
    return Renderer::VAO;
}

unsigned int Renderer::getEBO() {
    return Renderer::EBO;
}

void Renderer::destroy() {
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

Texture::Texture(int width, int height, int nrChannels, unsigned int texture) {
    Texture::width = width;
    Texture::height = height;
    Texture::nrChannels = nrChannels;

    Texture::texture = texture;
}