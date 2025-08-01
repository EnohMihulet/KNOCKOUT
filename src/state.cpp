#include "../include/state.h"
#include "../include/stateStack.h"

namespace knockOut {
    State::State(StateStack& stack, Context context)
        : _context(context), _stack(stack)
    {
    }
    
    void State::requestPush(StateID id) {
        _stack.pushState(id);
    }
    
    void State::requestPop() {
        _stack.popState();
    }
    
    void State::requestClear() {
        _stack.clearStates();
    }
}