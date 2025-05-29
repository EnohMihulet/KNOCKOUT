#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

namespace knockOut {

    class windowHelper {
    public:
        static sf::RenderWindow& createWindow();
        static void applyArcadeView(sf::RenderWindow& window, sf::View&  view);
    };
}

