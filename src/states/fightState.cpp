#include "../../include/states/fightState.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace knockOut {

    FightState::FightState(StateStack& stack, Context context) 
    : State(stack, context) , _player{Player(_context)} {
        _background.setTexture(_context.textures->get(Background1));
    }

    void FightState::handleEvent(const sf::Event& event) {
        _player.handleEvent(event);
    }

    void FightState::update(const sf::Time dt) {
        _player.update(dt);
        if (dt.asMicroseconds() > 1) {
            return;
        }
    }

    void FightState::draw() {
        _context._window->draw(_background);
        _player.draw();
    }
}