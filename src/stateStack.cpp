#include "../include/stateStack.h"
#include "../include/game.h"
#include "../include/states/mainMenuState.h"
#include "../include/states/fightState.h"
#include "../include/states/selectOpponentState.h"

namespace knockOut { 
    
    void StateStack::registerStates() {
        registerState<MainMenuState>(StateID::MainMenu);
        registerState<FightState>(StateID::Fight);
        registerState<SelectOpponentState>(StateID::SelectOpponent);
    }
    
    void StateStack::handleEvent(const sf::Event& event) {
        for (auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr) {
            (*itr)->handleEvent(event);
        }
        
        applyPendingChanges();
    }
    
    void StateStack::update(sf::Time dt) {
        for (auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr) {
            (*itr)->update(dt);
        }
        
        applyPendingChanges();
    }
    
    void StateStack::draw() {
        for (State::Ptr& state : _stack) {
            state->draw();
        }
    }
    
    void StateStack::pushState(StateID id) {
        _pending.push_back({Push, id});
    }
    
    void StateStack::popState() {
        _pending.push_back({Pop, StateID::None});
    }
    
    void StateStack::clearStates() {
        _pending.push_back({Clear, StateID::None});
    }
    
    bool StateStack::isEmpty() const {
        return _stack.empty();
    }
    
    void StateStack::applyPendingChanges() {
        for (PendingChange change : _pending) {
            switch (change.action) {
                case Push:
                    _stack.push_back(createState(change.stateID));
                    break;
                case Pop:
                    if (!_stack.empty()) {
                        _stack.pop_back();
                    }
                    break;
                case Clear:
                    _stack.clear();
                    break;
            }
        }
        
        _pending.clear();
    }
    
    State::Ptr StateStack::createState(StateID id) {
        auto found = _factories.find(id);
        if (found != _factories.end()) {
            return found->second();
        }
        return nullptr;
    }
}