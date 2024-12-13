#ifndef CLASE_PERSONAJE_HPP
#define CLASE_PERSONAJE_HPP

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

class Personaje {
public:
    Personaje(const std::string &texturePath, sf::Vector2f position) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("No se pudo cargar la textura desde: " + texturePath);
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(0.9f, 0.9f); // Ajuste del tamaño del personaje
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

    sf::Vector2f getSize() const {
        return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    }

    void reset(const sf::Vector2f &position) {
        sprite.setPosition(position);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif
