cmake_minimum_required(VERSION 3.5.0)
project(game VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(game 
               src/main.cpp
               src/glad.c             
               src/Shader.cpp
               src/Shader.hpp
               src/Game.hpp
               src/Game.cpp
               src/Renderer.hpp
               src/Renderer.cpp
               src/stb_image.h
               src/stb_image_implementation.cpp
               src/Player.hpp
               src/Player.cpp
               src/GameObject.hpp
               src/GameObject.cpp
               src/AnimatedObject.hpp
               src/AnimatedObject.cpp
               )

target_include_directories(game PUBLIC ~/include)

target_link_libraries(game 
                      glfw
                      OpenGL::GL    
                      )           