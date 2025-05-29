#include "../../include/characters/player.h"
#include "../../include/state.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace knockOut {

    Player::Player(State::Context context) 
    : _context(context) {
        _playerSprite.setTexture(_context.textures->get(PlayerTexture));
        loadLookupTable();
        _playerSprite.setTextureRect(_animations[(int) PlayerState::idle].frames[0]);
        _playerSprite.setScale({3,3});
        _playerSprite.setPosition({DESIGN_W / 2, DESIGN_H / 2});
        _animations[(int) _state].play(true);
    }

    void Player::loadLookupTable() {
        auto size = _playerSprite.getTexture()->getSize();
        const int fw = size.x / SHEET_COLS;
        const int fh = size.y / SHEET_ROWS;
        for (int i = 0; i < MOVE_COUNT; ++i) {
            MoveDef m = MOVE_DEFS[i];
            Animation a;
            for (int j = 0; j < m.count; ++j) {
                a.frames.push_back({fw * (m.startCol + j), fh * m.row, fw, fh});
            }
            a.frameTime = sf::seconds(m.frameTime);
            _animations[(int) m.state] = a;
        }
    }

    void Player::update(const sf::Time dt) {
        if(!_animations[_state].playing) {
            if (_bufferedMove) {
                _state = *_bufferedMove;
                _animations[_state].play();
                _bufferedMove.reset();
            } else {
                _state =  PlayerState::idle;
                _animations[_state].play(true);
            }
        }
        _animations[_state].update(dt);
        _playerSprite.setTextureRect(_animations[_state].frame());
    }
 
    void Player::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            auto x = INPUT_STATE_MAP.find(event.key.code);
            if (x == INPUT_STATE_MAP.end()) return;

            PlayerState requested = INPUT_STATE_MAP.at(event.key.code);

            if (!_animations[_state].playing || _state == PlayerState::idle) {
                _state = requested;
                _animations[_state].play(false);
            } else {
                _bufferedMove = requested;
            }
        }
    }

    void Player::draw() {
        _context._window->draw(_playerSprite);
    }
};