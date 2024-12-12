#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept> // Para manejar excepciones

class Personaje {
public:
    Personaje(const std::string& texturePath, sf::Vector2f position) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("No se pudo cargar la textura desde: " + texturePath);
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void move(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    sf::Vector2f getSize() const {
        return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    }

private:
    sf::Texture texture; // Almacena la textura cargada
    sf::Sprite sprite;   // Sprite que representa al personaje
};

int main() {
    sf::RenderWindow window(sf::VideoMode(384, 224), "DinoChrome");
    const float velocidad = 200.0f; // Velocidad en píxeles por segundo
    sf::Clock clock;

    // Cargar la imagen de fondo
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/urban-landscape-background-Preview.png")) {
        std::cerr << "Error: No se pudo cargar la imagen de fondo" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    try {
        // Ruta correcta de la imagen del personaje
        Personaje dino("assets/images/spr_enemy1_strip2.png", sf::Vector2f(0, 50));

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            float deltaTime = clock.restart().asSeconds();

            sf::Vector2f pos = dino.getPosition();
            sf::Vector2f size = dino.getSize();

            // Movimiento con límites en pantalla
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0) {
                dino.move(-velocidad * deltaTime, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x + size.x < window.getSize().x) {
                dino.move(velocidad * deltaTime, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pos.y > 0) {
                dino.move(0, -velocidad * deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pos.y + size.y < window.getSize().y) {
                dino.move(0, velocidad * deltaTime);
            }

            window.clear();
            window.draw(backgroundSprite); // Dibujar el fondo
            dino.draw(window);
            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
