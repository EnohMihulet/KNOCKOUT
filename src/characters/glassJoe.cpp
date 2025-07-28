#include "../../include/characters/glassJoe.h"
#include "../../include/helpers/resourceManager.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>

namespace knockOut {

    GlassJoe::GlassJoe(State::Context context) 
    : Opponent(context) {
        _sprite.setTexture(context.textures->get(TextureID::GlassJoe));
        loadLookupTable();
        _state = CharacterState::idle;
        _animations[(int) _state].play(true);
        _sprite.setScale({2,2});
        _sprite.setPosition(GLASS_JOE_START_POS);
    }

    void GlassJoe::loadLookupTable() {
        auto size = _sprite.getTexture()->getSize();
        const int fw = size.x / GLASS_JOE_SHEET_COLS;
        const int fh = size.y / GLASS_JOE_SHEET_ROWS;
        const auto& characterData = _context.characterMoveDefs->at(CharacterType::GlassJoe);
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

    void GlassJoe::handleEvent(const sf::Event& event) {
        if (event.key.code == sf::Keyboard::Q) {
            _state = taunt;
            _animations[_state].play(false);
        } if (event.key.code == sf::Keyboard::E) {
            _state = bDodge;
            _animations[_state].play(false);
        } if (event.key.code == sf::Keyboard::R) {
            _state = lDodge;
            _animations[_state].play(false);
        } if (event.key.code == sf::Keyboard::T) {
            _state = rDodge;
            _animations[_state].play(false);
        } if (event.key.code == sf::Keyboard::Y) {
            _state = duck;
            _animations[_state].play(false);
        }
    }

    void GlassJoe::update(const sf::Time dt) {
        
        bool animation_ended = _animations[_state].playing == false;

        if (!animation_ended) {
            _animations[_state].update();
            _sprite.setTextureRect(_animations[_state].frame());
            return;
        }

        srand(time(0));
        int random = rand() % 5;

        switch (random) {
            case 0:
                _state = idle;
                break;
            case 1:
                _state = taunt;
                break;
            case 2:
                _state = rJab;
                break;
            case 3:
                _state = rHook;
                break;
            case 4:
                _state = upperCut;
                break;
            default:
                _state = idle;
        }
        
        _animations[_state].play(false);
        _animations[_state].update();
        _sprite.setTextureRect(_animations[_state].frame());

        if (dt.asMicroseconds() > 0) return;
    }
}