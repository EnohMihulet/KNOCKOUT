#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <memory>
#include <vector>
#include "helpers/game.h"
#include "helpers/resourceManager.h"

namespace knockOut {

    class StateStack;
    enum class StateID;

    class State {  
    public:
        using Ptr = std::unique_ptr<State>;

        struct Context {
            sf::RenderWindow* _window;
            ResourceManager<sf::Texture, TextureID>* textures;
            ResourceManager<sf::Font, FontID>* fonts;
        };

        State(StateStack& stack, Context context)
            : _context(context), _stack(stack)
        {}

        virtual ~State() = default;

        virtual void handleEvent(const sf::Event& event) = 0;
        virtual void update(sf::Time dt) = 0;
        virtual void draw() = 0;

    protected:
        void requestPush(StateID id);
        void requestPop();
        void requestClear();

        Context _context;

    private:
        StateStack& _stack;
    };
}