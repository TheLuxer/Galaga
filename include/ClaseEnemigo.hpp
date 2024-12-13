#ifndef CLASE_ENEMIGO_HPP
#define CLASE_ENEMIGO_HPP

#include <SFML/Graphics.hpp>

class Enemigo {
public:
    Enemigo(const sf::Vector2f &position, sf::Texture &texture) : shootClock() {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(0.1f, 0.1f); // Ajuste del tamaño del enemigo para que sea proporcional
    }

    void move(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(sprite);
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    bool canShoot() {
        if (shootClock.getElapsedTime().asSeconds() > 2.0f) {
            shootClock.restart();
            return true;
        }
        return false;
    }

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
};

#endif
