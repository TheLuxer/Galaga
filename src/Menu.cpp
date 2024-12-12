#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdexcept> // Para manejar excepciones
#include <vector>

class Proyectil {
public:
    Proyectil(const sf::Vector2f& position) {
        shape.setSize(sf::Vector2f(10, 5)); // Tamaño del proyectil
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void move(float offsetX, float offsetY) {
        shape.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow& window) {
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
};

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

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    sf::Vector2f getSize() const {
        return sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1000), "Pantalla de Inicio Galaga");
    const float velocidad = 200.0f; // Velocidad en píxeles por segundo
    const float velocidadProyectil = 500.0f; // Velocidad del proyectil en píxeles por segundo
    sf::Clock clock;
    std::vector<Proyectil> proyectiles;

    // Cargar la imagen de fondo de la pantalla de inicio
    sf::Texture startBackgroundTexture;
    if (!startBackgroundTexture.loadFromFile("assets/images/out_of_depth_arcade.png")) {
        std::cerr << "Error: No se pudo cargar la imagen de fondo de la pantalla de inicio" << std::endl;
        return -1;
    }
    sf::Sprite startBackgroundSprite(startBackgroundTexture);

    // Ajustar el tamaño del fondo al tamaño de la ventana, pero un poco más angosto
    float scaleFactorX = (window.getSize().x / startBackgroundSprite.getLocalBounds().width) * 0.8f; // 80% del ancho original
    float scaleFactorY = window.getSize().y / startBackgroundSprite.getLocalBounds().height;
    startBackgroundSprite.setScale(scaleFactorX, scaleFactorY);
    startBackgroundSprite.setPosition((window.getSize().x - startBackgroundSprite.getGlobalBounds().width) / 2, 0);

    // Cargar la imagen de fondo del juego
    sf::Texture gameBackgroundTexture;
    if (!gameBackgroundTexture.loadFromFile("assets/images/Fondo.png")) {
        std::cerr << "Error: No se pudo cargar la imagen de fondo del juego" << std::endl;
        return -1;
    }
    sf::Sprite gameBackgroundSprite(gameBackgroundTexture);

    // Ajustar el tamaño del fondo del juego al tamaño de la ventana
    gameBackgroundSprite.setScale(
        window.getSize().x / gameBackgroundSprite.getLocalBounds().width,
        window.getSize().y / gameBackgroundSprite.getLocalBounds().height
    );

    // Cargar el audio
    sf::Music music;
    if (!music.openFromFile("assets/music/Cyberpunk-Moonlight-Sonata.ogg")) {
        std::cerr << "Error: No se pudo cargar el archivo de audio" << std::endl;
        return -1;
    }
    music.setLoop(true); // Hacer que el audio se repita
    music.play(); // Reproducir el audio

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
    title.setPosition(
        (window.getSize().x - title.getGlobalBounds().width) / 2,
        150
    );

    // Crear un texto para las instrucciones
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Presiona ENTER para comenzar");
    instructions.setCharacterSize(50);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setPosition(
        (window.getSize().x - instructions.getGlobalBounds().width) / 2,
        300
    );

    try {
        // Ruta correcta de la imagen del personaje
        Personaje dino("assets/images/spr_enemy1_strip2.png", sf::Vector2f(0, 50));

        // Pantalla de inicio
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
            window.draw(startBackgroundSprite); // Dibujar el fondo de la pantalla de inicio
            window.draw(title); // Dibujar el título
            window.draw(instructions); // Dibujar las instrucciones
            window.display();
        }

        // Juego principal
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

            // Disparar proyectil con la tecla Espacio
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                proyectiles.push_back(Proyectil(sf::Vector2f(pos.x + size.x, pos.y + size.y / 2)));
            }

            // Mover y dibujar proyectiles
            for (auto& proyectil : proyectiles) {
                proyectil.move(velocidadProyectil * deltaTime, 0);
            }

            // Eliminar proyectiles que salieron de la pantalla
            proyectiles.erase(
                std::remove_if(proyectiles.begin(), proyectiles.end(), [&window](const Proyectil& proyectil) {
                    return proyectil.getPosition().x > window.getSize().x;
                }),
                proyectiles.end()
            );

            window.clear();
            window.draw(gameBackgroundSprite); // Dibujar el fondo del juego
            dino.draw(window);
            for (auto& proyectil : proyectiles) {
                proyectil.draw(window);
            }
            window.display();

            // Esperar hasta que la música termine
            if (music.getStatus() != sf::Music::Playing) {
                window.close();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
