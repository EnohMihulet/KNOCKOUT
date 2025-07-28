#pragma once

#include "opponent.h"
#include "player.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace knockOut {

    const int GLASS_JOE_SHEET_COLS = 8;
    const int GLASS_JOE_SHEET_ROWS = 7;
    const sf::Vector2f GLASS_JOE_START_POS = {300, 150};

    class GlassJoe : public Opponent {
    public: 
        GlassJoe(State::Context context);

        void handleEvent(const sf::Event& event) override;
        void update(const sf::Time dt) override;
        void draw() {_context.window->draw(_sprite); }
        
    private:    
        void loadLookupTable() override;
    };

}