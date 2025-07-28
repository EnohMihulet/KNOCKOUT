#pragma once

#include "helpers/characterDataManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace knockOut {

    class StateStack;
    class Game;
    enum class StateID;
    enum class TextureID;
    enum class FontID;
    
    template<typename Resource, typename Identifier>
    class ResourceManager;
    
    class State {  
    public:
        using Ptr = std::unique_ptr<State>;
        
        struct Context {
            sf::RenderWindow* window;
            ResourceManager<sf::Texture, TextureID>* textures;
            ResourceManager<sf::Font, FontID>* fonts;
            std::unordered_map<CharacterType, std::vector<MoveDef>>* characterMoveDefs;
            CharacterType* selectedOpponent;
        };
        
        State(StateStack& stack, Context context);
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