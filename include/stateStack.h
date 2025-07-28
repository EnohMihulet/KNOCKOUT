#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <vector>
#include <map>
#include <memory>
#include "state.h"

namespace knockOut {
    // Forward declarations
    class Game;
    
    class StateStack {
    public:
        enum Action { Push, Pop, Clear };

        explicit StateStack(State::Context context)
        : _context(context) {}

        template<typename StateType>
        void registerState(StateID id) {
            _factories[id] = [this](){ return State::Ptr(new StateType(*this, _context)); };
        };
        
        void registerStates();
        void handleEvent(const sf::Event& event);
        void update(sf::Time dt);
        void draw();
        
        void pushState(StateID id);
        void popState();
        void clearStates();
        
        bool isEmpty() const;
        
    private:
        struct PendingChange { 
            Action action;
            StateID stateID; 
        };
        
        void applyPendingChanges();
        State::Ptr createState(StateID id);
        
        std::vector<State::Ptr> _stack;
        std::vector<PendingChange> _pending;
        std::map<StateID, std::function<State::Ptr()>> _factories;
        State::Context _context;
    };
}