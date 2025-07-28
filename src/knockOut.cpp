#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <cstdio>
#include "../include/game.h"

using namespace knockOut;

int main() {
    Game game = Game();
    game.run();

    return 0;
}