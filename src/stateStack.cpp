#include "../include/stateStack.h"
#include "../include/state.h"
#include "../include/states/mainMenuState.h"
#include "../include/states/selectOpponentState.h"
#include "../include/states/fightState.h"

namespace knockOut {

    void StateStack::registerStates() {
        // Circuit,
        // Fight,
        // Options,
        // Result
        registerState<MainMenuState>(StateID::MainMenu);
        registerState<SelectOpponentState>(StateID::SelectOpponent);
        registerState<FightState>(StateID::Fight);
    }

    void StateStack::handleEvent(sf::Event& event) {
        if (!_stack.empty()) {
            _stack.back()->handleEvent(event);
        }
        applyPendingChanges();
    }

    void StateStack::update(sf::Time dt){
        if (!_stack.empty()) {
            _stack.back()->update(dt);
        }
        applyPendingChanges();
    }

    void StateStack::draw() {
        for (auto& state : _stack)
            state->draw();
    }

    void StateStack::applyPendingChanges() {
        for (auto& change : _pending) {
            switch (change.action) {
                case Push:
                    _stack.push_back(_factories[change.stateID]());
                    break;
                case Pop:
                    _stack.pop_back();
                    break;
                case Clear:
                    _stack.clear();
                    break;
            }
        }
        _pending.clear();
    }
};