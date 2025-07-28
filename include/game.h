#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>
#include <optional>
#include "helpers/characterDataManager.h"
#include "stateStack.h"
#include "helpers/resourceManager.h"

namespace knockOut {
    const float DESIGN_W = 800.f, DESIGN_H = 600.f;
    
    enum class StateID {
        None,
        MainMenu,
        SelectOpponent,
        Circuit,
        Fight,
        Options,
        Result
    };
    
    enum class TextureID;
    enum class FontID;
    
    class Game {
    public:
        Game();
        void run();

        ResourceManager<sf::Texture, TextureID> _textures;
        ResourceManager<sf::Font, FontID> _fonts;
        sf::RenderWindow _window;
        CharacterDataManager _characterDataManager;
        CharacterType _opponent = CharacterType::GlassJoe;
    private:
        
        StateStack _stack;
    };
}