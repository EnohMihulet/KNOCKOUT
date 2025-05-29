#include <SFML/Window/GlResource.hpp>
#include "../include/state.h"
#include "../include/stateStack.h"

namespace knockOut {

    void State::requestPush(StateID id) {
        _stack.pushState(id);
    }

    void State::requestPop() {
        _stack.popState();
    }

    void State::requestClear() {
        _stack.clearStates();
    } 
};