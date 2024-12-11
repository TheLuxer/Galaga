#include <SFML/Graphics.hpp>
#include <iostream>

#define BLOCKS 90
#define blockSize 7

const int WIDTH = BLOCKS * blockSize;
const int HEIGHT = BLOCKS * blockSize;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Movimiento de la Nave");

class Nave {
public:
    sf::RectangleShape body;
    sf::Vector2f dir = {0, 0};

    Nave(sf::Vector2f position, sf::Color color) {
        body.setSize(sf::Vector2f(50.f, 50.f));
        body.setFillColor(color);
        body.setPosition(position);
    }

    void Move() {
        body.move(dir.x * blockSize, dir.y * blockSize);
    }

    void ChangeDirection() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            dir = {0, -1};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            dir = {0, 1};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            dir = {-1, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            dir = {1, 0};
    }

    void Draw() {
        window.draw(body);
    }
};

int main() {
    Nave nave({WIDTH / 2, HEIGHT / 2}, sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        nave.ChangeDirection();
        nave.Move();

        window.clear();
        nave.Draw();
        window.display();
    }

    return 0;
}
