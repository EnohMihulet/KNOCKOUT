#include <SFML/Window/VideoMode.hpp>
#include "../include/game.h"
#include "../include/helpers/windowHelper.h"

namespace knockOut {
    Game::Game() 
        : _window(sf::VideoMode(800, 600), "KNOCKOUT"
        , sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close)
        , _stack(State::Context{&_window, &_textures
            , &_fonts, &_characterDataManager._characterMoveDefs, &_opponent})
    {
        _window.setFramerateLimit(60);

        _textures.load(TextureID::Background1, "media/Ring_1.png");
        _textures.load(TextureID::Background2, "media/Ring_2.png");
        _textures.load(TextureID::Background3, "media/Ring_3.png");
        _textures.load(TextureID::BaldBull, "media/bald_bull.png");
        _textures.load(TextureID::GlassJoe, "media/glass_joe.png");
        _textures.load(TextureID::PlayerTexture, "media/little_mac.png");
    
        _fonts.load(FontID::MainFont, "media/PressStart2P-Regular.ttf");

        _characterDataManager.loadTable();
        
        _stack.registerStates();

        _stack.pushState(StateID::MainMenu);
    }
    
    void Game::run() {
        sf::View uiView(sf::FloatRect(0, 0, DESIGN_W, DESIGN_H));
        windowHelper::applyArcadeView(_window, uiView);

        sf::Clock clock;
        const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while (_window.isOpen()) {
            sf::Time dt = clock.restart();
            timeSinceLastUpdate += dt;

            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed){
                    _window.close();
                }
                else if (event.type == sf::Event::Resized) {
                    windowHelper::applyArcadeView(_window, uiView);
                }

                _stack.handleEvent(event);

            }

            while (timeSinceLastUpdate >= TimePerFrame) {
                timeSinceLastUpdate -= TimePerFrame;
                _stack.update(TimePerFrame);
            }

            _window.clear();
            _stack.draw();
            _window.display();
        }
    }
}