#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/GlResource.hpp>
#include <array>
#include <ratio>
#include <string>
#include <vector>
#include "../state.h"
#include "../helpers/uiHelper.h"
#include "../stateStack.h"

namespace knockOut {

    const std::string TITLE = "KNOCK-OUT";
    const std::array<std::string, 4> BUTTON_TEXT = {"FIGHT", "CIRCUIT", "OPTIONS", "QUIT"};

    const int BG_COUNT = 3;
    const sf::Time BG_INTERVAL = sf::seconds(.4);

    class MainMenuState : public State {
    public:
        MainMenuState(StateStack& stack, Context context);

        void handleEvent(const sf::Event& event) override;
        void update(const sf::Time dt) override;
        void draw() override;

    private:
        sf::Sprite _background;
        sf::Text _title;
        sf::Text _titleShadow;
        std::array<Button, 4> _buttons;
        int _selectedIndex = 0;
        int _bgIndex = 0;
        int _bgDirection = 1;
        sf::Time _bgElapsed = sf::Time::Zero;

        void updateLayout();
        void updateBackground(const sf::Time dt);
        void moveSelectedUp();
        void moveSelectedDown();
    };
};