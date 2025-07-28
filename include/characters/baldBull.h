#pragma once

#include "opponent.h"
#include "player.h"
#include <SFML/Window/Event.hpp>

namespace knockOut {

    const int BALD_BULL_SHEET_COLS = 4;
    const int BALD_BULL_SHEET_ROWS = 5;

    class BaldBull : public Opponent {
    public: 
        BaldBull(State::Context context);

        void handleEvent(const sf::Event& event) override;
        void update(const sf::Time dt) override;
        void draw() {_context.window->draw(_sprite); }
        
    private:    
        void loadLookupTable() override;
    };

}