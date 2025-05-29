#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include "../stateStack.h"
#include "../characters/player.h"

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
    };
};