#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(1920, 1000), "Pantalla de Inicio Galaga");

    // Cargar la fuente de texto TTF
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Eje.ttf")) {
        // Manejar el error si no se puede cargar la fuente
        return -1;
    }

    // Crear un texto para el título
    sf::Text title;
    title.setFont(font);
    title.setString("Bienvenido a Galaga");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setPosition(400 - title.getGlobalBounds().width / 2, 150);

    // Crear un texto para las instrucciones
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Presiona ENTER para comenzar");
    instructions.setCharacterSize(50);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setPosition(400 - instructions.getGlobalBounds().width / 2, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Verificar si se presiona ENTER para comenzar
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            break;
        }

        window.clear();
        window.draw(title);
        window.draw(instructions);
        window.display();
    }

    return 0;
}
