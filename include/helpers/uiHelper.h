#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace knockOut {
    struct Button {
        sf::Text text;
        sf::RectangleShape rect;

        bool isClicked(sf::RenderWindow* window, sf::Event event) {
            if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                return rect.getGlobalBounds().contains(mousePos);
            }
            return false;
        }

        void draw(sf::RenderWindow *window) {
            window->draw(rect);
            window->draw(text);
        }
    };
}
