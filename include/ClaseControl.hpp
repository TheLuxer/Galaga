#ifndef CLASE_CONTROL_HPP
#define CLASE_CONTROL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/ClasePersonaje.hpp"
#include "../include/ClaseProyectil.hpp"

class Control {
public:
    Control(Personaje &personaje, const float velocidad)
        : personaje(personaje), velocidad(velocidad) {}

    void update(float deltaTime, std::vector<Proyectil> &proyectiles, float velocidadProyectil) {
        sf::Vector2f pos = personaje.getPosition();
        sf::Vector2f size = personaje.getSize();

        // Movimiento del personaje con teclas de dirección y WASD
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && pos.x > 0) {
            personaje.move(-velocidad * deltaTime, 0);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && pos.x + size.x < 1920) {
            personaje.move(velocidad * deltaTime, 0);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && pos.y > 0) {
            personaje.move(0, -velocidad * deltaTime);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && pos.y + size.y < 1000) {
            personaje.move(0, velocidad * deltaTime);
        }

        // Disparar proyectil
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            proyectiles.push_back(Proyectil(sf::Vector2f(pos.x + size.x, pos.y + size.y / 2), sf::Vector2f(velocidadProyectil, 0)));
        }
    }

private:
    Personaje &personaje;
    const float velocidad;
};

#endif
