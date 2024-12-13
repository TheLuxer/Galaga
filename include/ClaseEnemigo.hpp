
#ifndef CLASEENEMIGO_HPP
#define CLASEENEMIGO_HPP

#include <SFML/Graphics.hpp>

class Enemigo {
public:
    Enemigo(const sf::Vector2f &position, sf::Texture &texture);
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    bool canShoot();

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
};

#endif // CLASEENEMIGO_HPP
