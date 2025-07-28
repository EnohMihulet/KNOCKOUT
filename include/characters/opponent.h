# pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "player.h"

namespace knockOut {

    class Opponent {
    public: 
        using Ptr = std::unique_ptr<Opponent>;

        Opponent(State::Context context) 
        : _context(context) {};
        virtual ~Opponent() = default;

        virtual void handleEvent(const sf::Event& event) = 0;
        virtual void update(const sf::Time dt) = 0;
        void draw() { _context.window->draw(_sprite); }

    protected:
        sf::Sprite _sprite;
        std::array<Animation, CHARACTER_STATE_NUMBER> _animations;
        CharacterState _state = CharacterState::idle;
        int q = 0;

        State::Context _context;

        virtual void loadLookupTable() = 0;
    };
}