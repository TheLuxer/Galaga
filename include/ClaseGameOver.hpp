
#ifndef CLASEGAMEOVER_HPP
#define CLASEGAMEOVER_HPP

#include <SFML/Graphics.hpp>

class PantallaGameOver {
public:
    PantallaGameOver(const sf::Font &font);
    void display(sf::RenderWindow &window);

private:
    sf::Text gameOverText;
};

#endif // CLASEGAMEOVER_HPP
