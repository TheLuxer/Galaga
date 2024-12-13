
#ifndef CLASEPERSONAJE_HPP
#define CLASEPERSONAJE_HPP

#include <SFML/Graphics.hpp>
#include <stdexcept>

class Personaje {
public:
    Personaje(const std::string &texturePath, sf::Vector2f position);
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getSize() const;
    void reset(const sf::Vector2f &position);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // CLASEPERSONAJE_HPP
