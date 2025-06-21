#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 coords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 proj;

void main() {

    TexCoords = coords;

    gl_Position = proj * model * vec4(pos, 1.0);
}