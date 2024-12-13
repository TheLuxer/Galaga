
#ifndef CLASEPROYECTIL_HPP
#define CLASEPROYECTIL_HPP

#include <SFML/Graphics.hpp>

class Proyectil {
public:
    Proyectil(const sf::Vector2f &position, const sf::Vector2f &velocity);
    void move(float deltaTime);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
};

#endif // CLASEPROYECTIL_HPP
