#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <vector>

#include "../helpers/uiHelper.h"
#include "../state.h"

namespace knockOut {

    const std::array<std::string, 9> OPPONENT_NAMES = {"0", "0", "0", "0","0", "0","0", "0","0"};

    class SelectOpponentState : public State {
    public:
        SelectOpponentState(StateStack& stack, Context context);

        void handleEvent(const sf::Event& event) override;
        void update(const sf::Time dt) override;
        void draw() override;

    private:
        sf::Sprite _background;
        sf::Text _title;
        sf::Text _titleShadow;
        Button _backButton;
        std::array<Button, 9> _opponents;
        int _selectedIndex = 0;
        int _bgIndex = 0;
        int _bgDirection = 1;
        sf::Time _bgElapsed = sf::Time::Zero;

        void updateLayout();
        void moveSelectedUp();
        void moveSelectedDown();
        void moveSelectedLeft();
        void moveSelectedRight();
        void updateBackground(const sf::Time dt);
    };
};