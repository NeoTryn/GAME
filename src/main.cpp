#include <iostream>

#include "Game.hpp"

#include <GLFW/glfw3.h>

int main() {

    Game game = {"CIA is watching me...", 800.0f, 600.0f};

    game.run();
    
    return 0;
}