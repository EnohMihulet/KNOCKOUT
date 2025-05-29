#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <cstdio>
#include "../include/stateStack.h"
#include "../include/helpers/game.h"
#include "../include/helpers/windowHelper.h"
#include "../include/helpers/resourceManager.h"

using namespace knockOut;

int main() {
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close;
    sf::RenderWindow window(sf::VideoMode(800, 600), "knockOut", style);
    window.setFramerateLimit(60);

    sf::View uiView(sf::FloatRect(0, 0, DESIGN_W, DESIGN_H));
    windowHelper::applyArcadeView(window, uiView);

    ResourceManager<sf::Font, FontID> fonts;
    fonts.load(MainFont, "../../Fonts/Press_Start_2P/PressStart2P-Regular.ttf");

    ResourceManager<sf::Texture, TextureID> textures;
    textures.load(Background1, "media/Ring_1.png");
    textures.load(Background2, "media/Ring_2.png");
    textures.load(Background3, "media/Ring_3.png");
    textures.load(BaldBull, "media/bald_bull.png");
    textures.load(PlayerTexture, "media/little_mac.png");
    
    State::Context context{ &window, &textures, &fonts};
    StateStack stateStack(context);

    stateStack.registerStates();
    stateStack.pushState(StateID::MainMenu);

    sf::Clock clock;
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                windowHelper::applyArcadeView(window, uiView);
            }

            stateStack.handleEvent(event);

        }

        while (timeSinceLastUpdate >= TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            stateStack.update(TimePerFrame);
        }

        window.clear();
        stateStack.draw();
        window.display();
    }

    return 0;
}