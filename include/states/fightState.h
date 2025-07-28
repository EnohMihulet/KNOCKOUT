#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include "../stateStack.h"
#include "../characters/player.h"
#include "../characters/baldBull.h"
#include "../characters/glassJoe.h"

namespace knockOut {

    class FightState : public State {
    public:
        FightState(StateStack& stack, Context context);

        void handleEvent(const sf::Event& event) override;
        void update(const sf::Time dt) override;
        void draw() override;

    private:
        sf::Sprite _background;
        int _bgIndex = 0;
        int _bgDirection = 1;
        sf::Time _bgElapsed = sf::Time::Zero;

        Player _player;
        Opponent::Ptr _opponent;

        std::unique_ptr<Opponent> createOpponent(CharacterType type, Context context) {
            switch (type) {
                case CharacterType::Player: return std::make_unique<BaldBull>(context); break;
                case CharacterType::BaldBull: return std::make_unique<BaldBull>(context); break;
                case CharacterType::GlassJoe: return std::make_unique<GlassJoe>(context); break;
                default: return std::make_unique<BaldBull>(context);
            }
        }
    };
};