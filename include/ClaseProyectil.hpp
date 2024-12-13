#ifndef CLASE_PROYECTIL_HPP
#define CLASE_PROYECTIL_HPP

#include <SFML/Graphics.hpp>

class Proyectil {
public:
    Proyectil(const sf::Vector2f &position, const sf::Vector2f &velocity) : velocity(velocity) {
        shape.setSize(sf::Vector2f(10, 5)); // Tamaño del proyectil
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void move(float deltaTime) {
        shape.move(velocity * deltaTime);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
};

#endif
