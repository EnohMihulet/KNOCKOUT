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
        _animations[(int) _state].play(false);
        _sprite.setScale({2,2});
        _sprite.setPosition(GLASS_JOE_START_POS);

        std::srand(static_cast<unsigned>(std::time(nullptr)));
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
        if (event.type == sf::Event::KeyPressed) return;
    }

    void GlassJoe::update(const sf::Time dt) {
        auto& anim = _animations[(int)_state];
        anim.update();
        _sprite.setTextureRect(anim.frame());

        if (anim.playing)
            return;

        if (_state == CharacterState::bodyHit) {
            _state = CharacterState::idle;
            _animations[(int)_state].play(false);
            return;
        }

        int r = std::rand() % 100;
        if (r < 20) {
            _state = CharacterState::taunt;
        } else if (r < 40) {
            _state = CharacterState::rJab;
        } else if (r < 60) {
            _state = CharacterState::rHook;
        } else if (r < 80) {
            _state = CharacterState::upperCut;
        } else {
            _state = CharacterState::idle;
        }

        _animations[(int)_state].play(false);
        _sprite.setTextureRect(_animations[(int)_state].frame());
        if (dt.asSeconds() > 0) return;
    }

    void GlassJoe::chooseNextAction() {
        if (_state == CharacterState::bodyHit && !_animations[(int)_state].playing) {
            _state = CharacterState::idle;
            _animations[(int)_state].play(true);
            return;
        }
        int r = rand() % 100;
        if (r < 60)       _state = CharacterState::rJab;
        else if (r < 80)  _state = CharacterState::rHook;
        else if (r < 90)  _state = CharacterState::upperCut;
        else              _state = CharacterState::taunt;
        _animations[(int)_state].play(false);
    }

}