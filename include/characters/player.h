#pragma once

#include "../state.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Touch.hpp>
#include <array>
#include <map>
#include <optional>
#include <queue>
#include <vector>

namespace knockOut {

    const int SHEET_COLS = 9;
    const int SHEET_ROWS = 3;
    const int MOVE_COUNT = 11;

    enum PlayerState {
        idle, jab, leftHook, rightHook, upperCut,
        bodyBlock, headBlock, leftDodge, rightDodge,
        leftHit, rightHit
    };

    struct MoveDef {PlayerState state; int row, startCol, count; float frameTime; };
    static constexpr MoveDef MOVE_DEFS[MOVE_COUNT] = {
        {PlayerState::idle, 0, 0, 2, .25},
        {PlayerState::jab, 0, 3, 2, .10},
        {PlayerState::bodyBlock, 0, 5, 1, .50},
        {PlayerState::headBlock, 0, 6, 1, .50},
        {PlayerState::leftDodge, 0, 7, 1, .50},        
        {PlayerState::rightDodge, 0, 8, 1, .50},
        {PlayerState::leftHook, 1, 0, 2, .15},
        {PlayerState::rightHook, 1, 2, 2, .15},
        {PlayerState::upperCut, 1, 4, 3, .20},
        {PlayerState::rightHit, 1, 7, 1, .75},
        {PlayerState::leftHit, 1, 8, 1, .75},
    };

    static const std::map<sf::Keyboard::Key, PlayerState> INPUT_STATE_MAP = {
        { sf::Keyboard::A, PlayerState::leftDodge   },
        { sf::Keyboard::D, PlayerState::rightDodge  },
        { sf::Keyboard::W, PlayerState::headBlock   },
        { sf::Keyboard::S, PlayerState::bodyBlock   },
        { sf::Keyboard::H, PlayerState::leftHook    },
        { sf::Keyboard::J, PlayerState::jab         },
        { sf::Keyboard::K, PlayerState::upperCut    },
        { sf::Keyboard::L, PlayerState::rightHook   }
    };


    struct Animation {
        std::vector<sf::IntRect> frames;
        sf::Time frameTime;
        bool looping;
        int current = 0;
        sf::Time elapsed = sf::Time::Zero;
        bool playing = false;

        void play(bool loop = false) {
            looping = loop;
            playing = true;
            current = 0;
            elapsed = sf::Time::Zero;
        }

        void update(sf::Time dt) {
            if (!playing) return;
            elapsed += dt;
            if (elapsed >= frameTime) {
                elapsed -= frameTime;
                current++;
                if (current >= (int) frames.size()) {
                    if (looping) current = 0;
                    else playing = false;
                }
            }
        }

        const sf::IntRect& frame() { return frames[current]; }
    };

    class Player {
        public:
            Player(State::Context context);

            void handleEvent(const sf::Event& event);
            void update(const sf::Time dt);
            void draw();

        private:
            sf::Sprite _playerSprite;
            std::array<Animation, MOVE_COUNT> _animations;
            PlayerState _state = PlayerState::idle;
            std::optional<PlayerState> _bufferedMove;

            State::Context _context;

            void loadLookupTable();
    };
}