#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../../include/states/fightState.h"
#include "../../include/helpers/resourceManager.h"

namespace knockOut {

    FightState::FightState(StateStack& stack, Context context) 
    : State(stack, context) , _player{Player(_context)}
    , _opponent(createOpponent(*context.selectedOpponent, context)) {
        
        _background.setTexture(_context.textures->get(TextureID::Background1));
    }

    void FightState::handleEvent(const sf::Event& event) {
        _opponent->handleEvent(event);
        _player.handleEvent(event);
    }

    void FightState::update(const sf::Time dt) {
    _player.update(dt);
    _opponent->update(dt);

    if (_player.isPunching()) {
        if (_player.getHitBox().intersects(_opponent->drawnBounds()) 
            && _opponent->isVulnerable()) {
            _opponent->takeHit();
        }
    }

    if (!_opponent->isInAnimation()) {
        _opponent->chooseNextAction();
    }
}

    void FightState::draw() {
        _context.window->draw(_background);
        _opponent->draw();
        _player.draw();
    }
    
}