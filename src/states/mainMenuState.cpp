#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstddef>
#include <iostream>
#include <ostream>
#include "../../include/states/mainMenuState.h"
#include "../../include/game.h"

namespace knockOut {

    MainMenuState::MainMenuState(StateStack& stack, Context context)
    : State(stack, context) {
        _background.setTexture(_context.textures->get(TextureID::Background1));

        _title.setFont(_context.fonts->get(FontID::MainFont));
        _title.setFillColor(sf::Color::Blue);
        _title.setString(TITLE);

        _titleShadow.setFont(_context.fonts->get(FontID::MainFont));
        _titleShadow.setFillColor(sf::Color::White);
        _titleShadow.setString(TITLE);

        for (size_t i = 0; i < BUTTON_TEXT.size(); ++i) {
            Button button;
            button.text.setFont(_context.fonts->get(FontID::MainFont));
            button.text.setFillColor(sf::Color::Blue);
            button.text.setString(BUTTON_TEXT[i]);

            _buttons[i] = button;
        }

        updateLayout();
    }

    void MainMenuState::updateLayout() {
        const float W = DESIGN_W, H = DESIGN_H;
        _title.setCharacterSize((unsigned)(H * 0.10f));
        _title.setOrigin(_title.getLocalBounds().width/2, _title.getLocalBounds().height/2);
        _title.setPosition(W/2, H * 0.12f);

        _titleShadow.setCharacterSize((unsigned)(H * 0.10f));
        _titleShadow.setOrigin(_title.getLocalBounds().width/2, _title.getLocalBounds().height/2);
        _titleShadow.setPosition(W/2, H * 0.13f);

        const float startY = H * 0.30f;
        const float spacing = H * 0.15f;
        for (size_t i = 0; i < _buttons.size(); ++i) {
            Button& b = _buttons[i];

            b.rect.setSize({W * 0.40f, H * 0.12f});
            b.rect.setOrigin(b.rect.getSize() / 2.f);
            b.rect.setPosition(W/2, startY + i * spacing);
            if (int(i) == _selectedIndex) b.rect.setFillColor(sf::Color::White);
            else b.rect.setFillColor(sf::Color::Red);

            b.text.setCharacterSize(static_cast<unsigned>(H * 0.05f));
            b.text.setOrigin(b.text.getLocalBounds().width/2, b.text.getLocalBounds().height/2);
            b.text.setPosition(b.rect.getPosition());
        }
    }

    void MainMenuState::moveSelectedUp() {
        if (_selectedIndex > 0) --_selectedIndex;
    }

    void MainMenuState::moveSelectedDown() {
        if (_selectedIndex < int(_buttons.size() - 1)) ++_selectedIndex;
    }

    void MainMenuState::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::Resized) {
            std::cout << _context.window->getSize().x << " " << _context.window->getSize().y << std::endl;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W) {
                moveSelectedUp();
                updateLayout();
            } else if (event.key.code == sf::Keyboard::S) {
                moveSelectedDown();
                updateLayout();
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (_selectedIndex == 0) {
                    requestClear();
                    requestPush(StateID::SelectOpponent);
                    return;
                } else  if (_selectedIndex == 1) {
                    requestClear();
                    requestPush(StateID::Circuit);
                    return;
                } else if (_selectedIndex ==  2) {
                    requestClear();
                    requestPush(StateID::Options);
                    return;
                } else if (_selectedIndex == 3) {
                    _context.window->close();
                } 
            }
        }

        for (size_t i = 0; i < _buttons.size(); ++i) {
            auto& b = _buttons[i];

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = _context.window->mapPixelToCoords(sf::Mouse::getPosition(*_context.window));
                if (b.rect.getGlobalBounds().contains(mousePos)) {
                    _selectedIndex = i;
                    updateLayout();
                }
            }

            if (b.isClicked(_context.window, event)) {
                if (b.text.getString() == "FIGHT") {
                    requestClear();
                    requestPush(StateID::SelectOpponent);
                } else  if (b.text.getString() == "CIRCUIT") {
                    requestClear();
                    requestPush(StateID::Circuit);
                } else if (b.text.getString() == "OPTIONS") {
                    requestClear();
                    requestPush(StateID::Options);
                } else if (b.text.getString() == "QUIT") {
                    _context.window->close();
                }   
            }
        }
    }

    void MainMenuState::updateBackground(const sf::Time dt) {
        _bgElapsed += dt;
        if (_bgElapsed >= BG_INTERVAL) {
            _bgElapsed = sf::Time::Zero;
            _bgIndex += _bgDirection;

            if (_bgIndex == 0 || _bgIndex == BG_COUNT - 1) {
                _bgDirection = -_bgDirection;
            }

            TextureID id;
            switch (_bgIndex) {
                case 0: id = TextureID::Background1; break;
                case 1: id = TextureID::Background2; break;
                case 2: id = TextureID::Background3; break;
                default: id = TextureID::Background1; break;
            }

            _background.setTexture(_context.textures->get(id));
        }
    }

    void MainMenuState::update(sf::Time dt) {
        updateBackground(dt);
    }

    void MainMenuState::draw() {
        _context.window->draw(_background);
        _context.window->draw(_titleShadow);
        _context.window->draw(_title);
        for (Button& b : _buttons) b.draw(_context.window);
    }
}