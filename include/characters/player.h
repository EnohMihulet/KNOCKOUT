#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Touch.hpp>
#include <array>
#include <map>
#include <optional>
#include <queue>
#include <vector>
#include "../state.h"
#include "../helpers/characterDataManager.h"

namespace knockOut { 

    const int SHEET_COLS = 9;
    const int SHEET_ROWS = 3;
    const sf::Vector2f PLAYER_START_POS = { 350, 300};
    const sf::Time INPUT_COOLDOWN_TIME = sf::seconds(.05f);

    static const std::map<sf::Keyboard::Key, CharacterState> INPUT_STATE_MAP = {
        { sf::Keyboard::A, CharacterState::lDodge   },
        { sf::Keyboard::D, CharacterState::rDodge  },
        { sf::Keyboard::W, CharacterState::headBlock   },
        { sf::Keyboard::S, CharacterState::bodyBlock   },
        { sf::Keyboard::H, CharacterState::lHook    },
        { sf::Keyboard::J, CharacterState::rJab         },
        { sf::Keyboard::K, CharacterState::upperCut    },
        { sf::Keyboard::L, CharacterState::rHook   }
    };

    struct Animation {
        std::vector<sf::IntRect> animationFrames;
        std::vector<int> animationTimes;
        bool looping;
        int current = 0;
        int framesElapsed = 0;
        bool playing = false;

        void play(bool loop = false) {
            looping = loop;
            playing = true;
            current = 0;
            framesElapsed = 0;
        }

        void update() {
            if (!playing) return;
            ++framesElapsed;
            if (framesElapsed >= animationTimes[current]) {
                framesElapsed = 0;
                current++;
                if (current >= (int) animationFrames.size()) {
                    if (looping) current = 0;
                    else playing = false;
                }
            }
        }

        const sf::IntRect& frame() { return animationFrames[current]; }
    };

    class Player {
    public:
        Player(State::Context context);

        void handleEvent(const sf::Event& event);
        void update(const sf::Time dt);
        void draw();
        
        sf::FloatRect getHitBox() const;
        bool isPunching() const;
        int getDamage() const;

    private:
        sf::Sprite _playerSprite;
        std::array<Animation, CHARACTER_STATE_NUMBER> _animations;
        CharacterState _state = CharacterState::idle;
        std::optional<CharacterState> _bufferedMove;
        sf::Time _inputCooldown = sf::Time::Zero;

        State::Context _context;

        void loadLookupTable();
    };

}