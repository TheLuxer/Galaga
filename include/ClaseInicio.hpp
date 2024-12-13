
#ifndef CLASEINICIO_HPP
#define CLASEINICIO_HPP

#include <SFML/Graphics.hpp>

class PantallaInicio {
public:
    PantallaInicio(const std::string &backgroundPath, const sf::Font &font);
    void display(sf::RenderWindow &window);
    bool isStartPressed() const;

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text title;
    sf::Text instructions;
};

#endif // CLASEINICIO_HPP
