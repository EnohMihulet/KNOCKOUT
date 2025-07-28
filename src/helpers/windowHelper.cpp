#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>

#include "../../include/helpers/windowHelper.h"
#include "../../include/game.h"


namespace knockOut {

    void windowHelper::applyArcadeView(sf::RenderWindow& window, sf::View& view) {
        auto windowSize = window.getSize();
        float scaleX = windowSize.x / float(DESIGN_W);
        float scaleY = windowSize.y / float(DESIGN_H);

        float scale = std::min(scaleX, scaleY);

        float viewportW = (DESIGN_W * scale) / windowSize.x;
        float viewportH = (DESIGN_H * scale) / windowSize.y;

        float offsetX = (1.f - viewportW) / 2.f;
        float offsetY = (1.f - viewportH) / 2.f;

        view.setSize( float(DESIGN_W), float(DESIGN_H) );
        view.setViewport({ offsetX, offsetY, viewportW, viewportH });
        window.setView(view);
    }
}