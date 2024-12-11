#include <SFML/Graphics.hpp>
#include <iostream>

#define BLOCKS 90
#define blockSize 7

const int WIDTH = BLOCKS * blockSize;
const int HEIGHT = BLOCKS * blockSize;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Movimiento de la Nave", sf::Style::Fullscreen);

class Nave {
public:
    sf::RectangleShape body;
    sf::Vector2f dir = {0, 0};
    float speed = 5000.0f; // Velocidad en píxeles por segundo

    Nave(sf::Vector2f position, sf::Color color) {
        body.setSize(sf::Vector2f(50.f, 50.f));
        body.setFillColor(color);
        body.setPosition(position);
    }

    void Move(float deltaTime) {
        // Calcular nueva posición
        sf::Vector2f newPos = body.getPosition() + dir * speed * deltaTime;

        // Asegurar que no salga de los límites de la pantalla
        if (newPos.x < 0)
            newPos.x = 0;
        if (newPos.x + body.getSize().x > WIDTH)
            newPos.x = WIDTH - body.getSize().x;
        if (newPos.y < 0)
            newPos.y = 0;
        if (newPos.y + body.getSize().y > HEIGHT)
            newPos.y = HEIGHT - body.getSize().y;

        body.setPosition(newPos);
    }

    void ChangeDirection() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            dir = {0, -1};
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            dir = {0, 1};
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            dir = {-1, 0};
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            dir = {1, 0};
        else
            dir = {0, 0}; // Detener la nave si no se presionan teclas
    }

    void Draw() {
        window.draw(body);
    }
};

int main() {
    Nave nave({WIDTH / 2, HEIGHT / 2}, sf::Color::Blue);
    sf::Clock clock; // Reloj para medir el tiempo transcurrido

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        float deltaTime = clock.restart().asSeconds(); // Tiempo transcurrido en segundos

        nave.ChangeDirection();
        nave.Move(deltaTime);

        window.clear();
        nave.Draw();
        window.display();
    }

    return 0;
}
