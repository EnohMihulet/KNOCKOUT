#include "../../include/characters/baldBull.h"
#include "../../include/helpers/resourceManager.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>

namespace knockOut {

    BaldBull::BaldBull(State::Context context) 
    : Opponent(context) {
        _sprite.setTexture(context.textures->get(TextureID::BaldBull));
        loadLookupTable();
        _state = CharacterState::idle;
        _sprite.setScale({2,2});
        _sprite.setPosition({800 / 2.f, 400 / 2.f});
        _animations[(int) _state].play(true);
    }

    void BaldBull::loadLookupTable() {
        auto size = _sprite.getTexture()->getSize();
        const int fw = size.x / BALD_BULL_SHEET_COLS;
        const int fh = size.y / BALD_BULL_SHEET_ROWS;
        const auto& characterData = _context.characterMoveDefs->at(CharacterType::BaldBull);
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

    void BaldBull::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) return;
    }

    void BaldBull::update(const sf::Time dt) {
        if (_animations[_state].playing == false) {
            _state = idle;
            _animations[_state].play(true);
        }
        _animations[_state].update();
        _sprite.setTextureRect(_animations[_state].frame());
        if (dt.asMicroseconds() > 0) return;
    }

    void BaldBull::chooseNextAction() {
        return;
    }
}