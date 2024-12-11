#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Crear la nave
    sf::ConvexShape ship;
    ship.setPointCount(4);
    ship.setPoint(0, sf::Vector2f(150, 100));  // Punta superior
    ship.setPoint(1, sf::Vector2f(100, 200));  // Esquina inferior izquierda
    ship.setPoint(2, sf::Vector2f(150, 180));  // Centro inferior
    ship.setPoint(3, sf::Vector2f(200, 200));  // Esquina inferior derecha
    ship.setFillColor(sf::Color::Blue);

    // Posición inicial de la nave
    sf::Vector2f position(300, 400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimiento de la nave
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            position.x -= 2.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            position.x += 2.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            position.y -= 2.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            position.y += 2.0f;

        // Actualizar la posición de la nave
        ship.setPosition(position);

        window.clear();

        // Dibujar la nave
        window.draw(ship);

        window.display();
    }

    return 0;
}
