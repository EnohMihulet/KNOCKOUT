#pragma once


#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <vector>
#include <map>
#include "state.h"

namespace knockOut {

    class State;
    enum class StateID;

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

        void handleEvent(sf::Event& event);
        void update(sf::Time dt);
        void draw();

        void pushState(StateID id) { _pending.push_back({Push, id}); };
        void popState() { _pending.push_back({Pop, StateID::None}); };
        void clearStates() { _pending.push_back({Clear, StateID::None}); };

    private:

        struct PendingChange { 
            Action action;
            StateID stateID; 
        };

        void applyPendingChanges();

        std::vector<State::Ptr> _stack;
        std::vector<PendingChange> _pending;
        std::map<StateID, std::function<State::Ptr()>> _factories;
        State::Context _context;
    };
}
