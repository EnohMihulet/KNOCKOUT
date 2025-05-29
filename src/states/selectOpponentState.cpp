#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../../include/states/selectOpponentState.h"
#include "../../include/states/mainMenuState.h"

namespace knockOut {

    SelectOpponentState::SelectOpponentState(StateStack& stack, Context context) 
        : State(stack, context) {
            _background.setTexture(_context.textures->get(Background1));

            _title.setFont(_context.fonts->get(MainFont));
            _title.setFillColor(sf::Color::Blue);
            _title.setString("FIGHT");

            _titleShadow.setFont(_context.fonts->get(MainFont));
            _titleShadow.setFillColor(sf::Color::White);
            _titleShadow.setString("FIGHT");

            _backButton.text.setFont(_context.fonts->get(MainFont));
            _backButton.text.setFillColor(sf::Color::Blue);
            _backButton.text.setString("BACK");

            for (size_t i = 0; i < OPPONENT_NAMES.size(); ++i) {
                Button button;
                button.text.setFont(_context.fonts->get(MainFont));
                button.text.setFillColor(sf::Color::Blue);
                button.text.setString(OPPONENT_NAMES[i]);

                _opponents[i] = button;
            }
            updateLayout(); 
        }

    void SelectOpponentState::updateLayout() {
        const float W = DESIGN_W, H = DESIGN_H;
        _title.setCharacterSize(H * .10f); 
        _title.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);
        _title.setPosition(W / 2, H * .10f);

        _titleShadow.setCharacterSize(H * .10f); 
        _titleShadow.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);
        _titleShadow.setPosition(W / 2, H * .11f);

        _backButton.text.setCharacterSize(H * .05f);
        _backButton.text.setOrigin(_backButton.text.getGlobalBounds().width / 2, _backButton.text.getGlobalBounds().height / 2);
        _backButton.text.setPosition(W * .10f, H * .05f);
        if (_selectedIndex == 9) _backButton.text.setFillColor(sf::Color::White);
        else _backButton.text.setFillColor(sf::Color::Blue);

        _backButton.rect.setSize({_backButton.text.getGlobalBounds().width, _backButton.text.getGlobalBounds().height});
        _backButton.rect.setOrigin(_backButton.rect.getSize() / 2.f);
        _backButton.rect.setPosition(W * .10f, H * .05f);
        _backButton.rect.setFillColor(sf::Color::Transparent);

        const float startY = H * 0.30f;
        const float startX = W * 0.25f;
        const float spacingY = H * 0.25f;
        const float spacingX = W * 0.25f;
        for (int y = 0; y < 3; ++y) {
            for (int x = 0; x < 3; ++x) {
                int index = y * 3 + x;
                auto& b = _opponents[index];

                b.rect.setSize({W * 0.20f, H * 0.20f});
                b.rect.setOrigin(b.rect.getSize() / 2.f);                             
                
                b.rect.setPosition(startX + spacingX * x, startY + spacingY * y);
                if (index == _selectedIndex) b.rect.setFillColor(sf::Color::White);
                else b.rect.setFillColor(sf::Color::Red);

                b.text.setCharacterSize(static_cast<unsigned>(H * 0.05f));
                b.text.setOrigin(b.text.getLocalBounds().width/2, b.text.getLocalBounds().height/2);
                b.text.setPosition(b.rect.getPosition());
            }
        }
    }

    void SelectOpponentState::moveSelectedUp() {
        if (_selectedIndex == 9) return;

        if (_selectedIndex > 2) _selectedIndex -= 3;
        else _selectedIndex = 9;
    }

    void SelectOpponentState::moveSelectedDown() {
        if (_selectedIndex == 9) _selectedIndex = 0;
        else if (_selectedIndex < int(_opponents.size() - 3)) _selectedIndex += 3;
    }

    void SelectOpponentState::moveSelectedLeft() {
        if (_selectedIndex == 9) return;

        if (_selectedIndex > 0) --_selectedIndex;
        else _selectedIndex = 9;
    }

    void SelectOpponentState::moveSelectedRight() {
        if (_selectedIndex == 9) _selectedIndex = 0;
        else if (_selectedIndex < int(_opponents.size() - 1)) ++_selectedIndex;
    }
    
    void SelectOpponentState::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W) {
                moveSelectedUp();
                updateLayout();
            } else if (event.key.code == sf::Keyboard::S) {
                moveSelectedDown();
                updateLayout();
            } else if (event.key.code == sf::Keyboard::D) {
                moveSelectedRight();
                updateLayout();
            } else if (event.key.code == sf::Keyboard::A) {
                moveSelectedLeft();
                updateLayout();
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (_selectedIndex == 9) {
                    requestClear();
                    requestPush(StateID::MainMenu);
                }
                else {
                    requestClear();
                    requestPush(StateID::Fight);
                }
            }
        }
        if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = _context._window->mapPixelToCoords(sf::Mouse::getPosition(*_context._window));
            if (_backButton.rect.getGlobalBounds().contains(mousePos)) {
                _backButton.text.setFillColor(sf::Color::White);
            } else {
                _backButton.text.setFillColor(sf::Color::Blue);
            }

            if (_backButton.isClicked(_context._window, event)) {
                requestClear();
                requestPush(StateID::MainMenu);
            }
            
            for (size_t i = 0; i < _opponents.size(); ++i) {
                auto& b = _opponents[i];
     
                if (b.rect.getGlobalBounds().contains(mousePos)) {
                    _selectedIndex = i;
                    updateLayout();
                }

                if (b.isClicked(_context._window, event)) {
                    requestClear();
                    requestPush(StateID::Fight);
                }
            }
        }
    }

    void SelectOpponentState::updateBackground(const sf::Time dt) {
        _bgElapsed += dt;
        if (_bgElapsed >= BG_INTERVAL) {
            _bgElapsed = sf::Time::Zero;
            _bgIndex += _bgDirection;

            if (_bgIndex == 0 || _bgIndex == BG_COUNT - 1) {
                _bgDirection = -_bgDirection;
            }

            TextureID id;
            switch (_bgIndex) {
                case 0: id = Background1; break;
                case 1: id = Background2; break;
                case 2: id = Background3; break;
                default: id = Background1; break;
            }

            _background.setTexture(_context.textures->get(id));
        }
    }

    void SelectOpponentState::update(sf::Time dt) {
        updateBackground(dt);
    }

    void SelectOpponentState::draw() {
        _context._window->draw(_background);
        _backButton.draw(_context._window);
        _context._window->draw(_titleShadow);
        _context._window->draw(_title);
        for (auto& b : _opponents) b.draw(_context._window);
    }
};