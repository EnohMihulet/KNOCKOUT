#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../../include/characters/player.h"
#include "../../include/game.h"

namespace knockOut { 

    Player::Player(State::Context context) 
    : _context(context) {
        _playerSprite.setTexture(_context.textures->get(TextureID::PlayerTexture));
        loadLookupTable();
        _playerSprite.setTextureRect(_animations[(int) CharacterState::idle].animationFrames[0]);
        _playerSprite.setScale({4,4});
        _playerSprite.setPosition(PLAYER_START_POS);
        _animations[(int) _state].play(true);
    }

    void Player::loadLookupTable() {
        auto size = _playerSprite.getTexture()->getSize();
        const int fw = size.x / SHEET_COLS;
        const int fh = size.y / SHEET_ROWS;
        const auto& characterData = _context.characterMoveDefs->at(CharacterType::Player);
        for (int i = 0; i < (int) characterData.size(); ++i) {
            MoveDef m = characterData[i];
            Animation a;
            for (int j = 0; j < (int) m.frameTimes.size(); ++j) {
                a.animationFrames.push_back({fw * (m.startCol + j), fh * m.row, fw, fh});
            }
            a.animationTimes = m.frameTimes;
            _animations[(int) m.state] = a;
        }
    }

    void Player::update(const sf::Time dt) {
        _inputCooldown -= dt;
        if (_inputCooldown.asSeconds() > 0) return;


        if(!_animations[_state].playing) {
            if (_bufferedMove) {
                _state = *_bufferedMove;
                _animations[_state].play();
                _bufferedMove.reset();
            } else {
                _state =  CharacterState::idle;
                _animations[_state].play(true);
            }
            _inputCooldown = INPUT_COOLDOWN_TIME;
        }
        _animations[_state].update();
        _playerSprite.setTextureRect(_animations[_state].frame());
    }
 
    void Player::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            auto x = INPUT_STATE_MAP.find(event.key.code);
            if (x == INPUT_STATE_MAP.end()) return;

            CharacterState requested = INPUT_STATE_MAP.at(event.key.code);

            if (!_animations[_state].playing || _state == CharacterState::idle) {
                _state = requested;
                _animations[_state].play(false);
            } else {
                _bufferedMove = requested;
            }
        }
    }

    void Player::draw() {
        _context.window->draw(_playerSprite);
    }

    sf::FloatRect Player::getHitBox() const { return _playerSprite.getGlobalBounds(); }

    bool Player::isPunching() const {
        return _state == CharacterState::rJab ||
            _state == CharacterState::lHook ||
            _state == CharacterState::rHook ||
            _state == CharacterState::upperCut;
    }

    int Player::getDamage() const {
        switch(_state) {
        case CharacterState::rJab: return 1;
        case CharacterState::lHook:
        case CharacterState::rHook: return 2;
        case CharacterState::upperCut: return 3;
        default: return 0;
        }
    }
};