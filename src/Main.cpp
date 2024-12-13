#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdexcept> // Para manejar excepciones
#include <vector>
#include <cstdlib>

// Clase Proyectil
class Proyectil {
public:
    Proyectil(const sf::Vector2f &position, const sf::Vector2f &velocity) : velocity(velocity) {
        shape.setSize(sf::Vector2f(10, 5)); // Tamaño del proyectil
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void move(float deltaTime) {
        shape.move(velocity * deltaTime);
    }

    void draw(sf::RenderWindow &window) {
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
    sf::Vector2f velocity;
};

// Clase Personaje
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

// Clase Enemigo
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

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1000), "Pantalla de Inicio Galaga");
    const float velocidad = 200.0f;          // Velocidad en píxeles por segundo
    const float velocidadProyectil = 500.0f; // Velocidad del proyectil en píxeles por segundo
    const float velocidadEnemigo = 100.0f;   // Velocidad del enemigo en píxeles por segundo
    sf::Clock clock;
    sf::Clock gameClock; // Reloj para medir el tiempo jugado
    std::vector<Proyectil> proyectiles;
    std::vector<Proyectil> proyectilesEnemigos;
    std::vector<Enemigo> enemigos;

    // Cargar la imagen de fondo de la pantalla de inicio
    sf::Texture startBackgroundTexture;
    if (!startBackgroundTexture.loadFromFile("assets/images/Arcade.png")) {
        std::cerr << "Error: No se pudo cargar la imagen de fondo de la pantalla de inicio" << std::endl;
        return -1;
    }
    sf::Sprite startBackgroundSprite(startBackgroundTexture);

    // Ajustar el tamaño del fondo al tamaño de la ventana
    float scaleFactorX = (window.getSize().x / startBackgroundSprite.getLocalBounds().width) * 0.7f; // 70% del ancho original
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
    gameBackgroundSprite.setScale(
        window.getSize().x / gameBackgroundTexture.getSize().x,
        window.getSize().y / gameBackgroundTexture.getSize().y);

    // Cargar la textura de los enemigos
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("assets/images/Ovi.png")) {
        std::cerr << "Error: No se pudo cargar la textura del enemigo" << std::endl;
        return -1;
    }

    // Cargar el audio
    sf::Music music;
    if (!music.openFromFile("assets/music/Cyberpunk-Moonlight-Sonata.ogg")) {
        std::cerr << "Error: No se pudo cargar el archivo de audio" << std::endl;
        return -1;
    }
    music.setLoop(true);
    music.play();

    // Cargar la fuente de texto TTF
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/retro.ttf")) {
        return -1;
    }

    // Crear un texto para el título
    sf::Text title;
    title.setFont(font);
    title.setString("Bienvenido a Sky Rider");
    title.setCharacterSize(150);
    title.setFillColor(sf::Color::White);
    title.setPosition(
        (window.getSize().x - title.getGlobalBounds().width) / 2,
        300);

    // Crear un texto para las instrucciones
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Presiona ENTER para comenzar");
    instructions.setCharacterSize(75);
    instructions.setFillColor(sf::Color::Yellow);
    instructions.setPosition(
        (window.getSize().x - instructions.getGlobalBounds().width) / 2,
        450);
    // Crear un texto para mostrar el tiempo jugado
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // Crear un texto para mostrar "Game Over"
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(
        (window.getSize().x - gameOverText.getGlobalBounds().width) / 2,
        (window.getSize().y - gameOverText.getGlobalBounds().height) / 2);

    try {
        // Ruta correcta de la imagen del personaje
        Personaje dino("assets/images/Avion.png", sf::Vector2f(0, 50));

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
                gameClock.restart(); // Reiniciar el reloj al comenzar el juego
                break;
            }

            window.clear();
            window.draw(startBackgroundSprite);
            window.draw(title);
            window.draw(instructions);
            window.display();
        }

        // Juego principal
        sf::Clock enemySpawnClock;
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

            // Actualizar tiempo jugado
            float gameTime = gameClock.getElapsedTime().asSeconds();
            scoreText.setString("Score: " + std::to_string(static_cast<int>(gameTime)) + "");

            // Movimiento del personaje con teclas de dirección y WASD
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && pos.x > 0) {
                dino.move(-velocidad * deltaTime, 0);
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && pos.x + size.x < window.getSize().x) {
                dino.move(velocidad * deltaTime, 0);
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && pos.y > 0) {
                dino.move(0, -velocidad * deltaTime);
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && pos.y + size.y < window.getSize().y) {
                dino.move(0, velocidad * deltaTime);
            }

            // Disparar proyectil
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                proyectiles.push_back(Proyectil(sf::Vector2f(pos.x + size.x, pos.y + size.y / 2), sf::Vector2f(velocidadProyectil, 0)));
            }

            // Mover proyectiles
            for (auto &proyectil : proyectiles) {
                proyectil.move(deltaTime);
            }

            // Mover proyectiles enemigos
            for (auto &proyectil : proyectilesEnemigos) {
                proyectil.move(deltaTime);
            }

            // Eliminar proyectiles fuera de la pantalla
            proyectiles.erase(
                std::remove_if(proyectiles.begin(), proyectiles.end(), [&window](const Proyectil &proyectil) {
                    return proyectil.getPosition().x > window.getSize().x;
                }),
                proyectiles.end());

            proyectilesEnemigos.erase(
                std::remove_if(proyectilesEnemigos.begin(), proyectilesEnemigos.end(), [&window](const Proyectil &proyectil) {
                    return proyectil.getPosition().y > window.getSize().y || proyectil.getPosition().y < 0;
                }),
                proyectilesEnemigos.end());

            // Generar enemigos periódicamente
            if (enemySpawnClock.getElapsedTime().asSeconds() > 2.0f) {
                enemigos.push_back(Enemigo(sf::Vector2f(window.getSize().x, rand() % window.getSize().y), enemyTexture));
                enemySpawnClock.restart();
            }

            // Mover enemigos y disparar
            for (auto &enemigo : enemigos) {
                enemigo.move(-velocidadEnemigo * deltaTime, 0);
                if (enemigo.canShoot()) {
                    proyectilesEnemigos.push_back(Proyectil(sf::Vector2f(enemigo.getPosition().x, enemigo.getPosition().y + 15), sf::Vector2f(-velocidadProyectil, 0)));
                }
            }

            // Eliminar enemigos fuera de la pantalla
            enemigos.erase(
                std::remove_if(enemigos.begin(), enemigos.end(), [&window](const Enemigo &enemigo) {
                    return enemigo.getPosition().x + enemigo.getBounds().width < 0;
                }),
                enemigos.end());

            // Detección de colisiones entre proyectiles enemigos y el jugador
            for (auto &proyectil : proyectilesEnemigos) {
                if (proyectil.getBounds().intersects(dino.getBounds())) {
                    // Mostrar pantalla de Game Over
                    window.clear();
                    window.draw(gameBackgroundSprite);
                    window.draw(gameOverText);
                    window.display();

                    // Pausar para que el jugador vea el mensaje
                    sf::sleep(sf::seconds(3));

                    // Reiniciar a la pantalla principal
                    while (true) {
                        sf::Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == sf::Event::Closed) {
                                window.close();
                                return 0;
                            }
                        }

                        // Mostrar pantalla principal nuevamente
                        window.clear();
                        window.draw(startBackgroundSprite);
                        window.draw(title);
                        window.draw(instructions);
                        window.display();

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            // Reiniciar el juego
                            proyectiles.clear();
                            proyectilesEnemigos.clear();
                            enemigos.clear();
                            dino.reset(sf::Vector2f(0, 50));
                            gameClock.restart();
                            break;
                        }
                    }
                    break;
                }
            }

            // Detección de colisiones entre proyectiles y enemigos
            for (auto enemigoIt = enemigos.begin(); enemigoIt != enemigos.end();) {
                bool enemigoImpactado = false;
                for (auto proyectilIt = proyectiles.begin(); proyectilIt != proyectiles.end();) {
                    if (proyectilIt->getBounds().intersects(enemigoIt->getBounds())) {
                        // Eliminar proyectil y marcar enemigo como impactado
                        proyectilIt = proyectiles.erase(proyectilIt);
                        enemigoImpactado = true;
                        break;
                    } else {
                        ++proyectilIt;
                    }
                }
                if (enemigoImpactado) {
                    enemigoIt = enemigos.erase(enemigoIt);
                } else {
                    ++enemigoIt;
                }
            }

            // Dibujar todo en pantalla
            window.clear();
            window.draw(gameBackgroundSprite);
            dino.draw(window);
            for (auto &proyectil : proyectiles) {
                proyectil.draw(window);
            }
            for (auto &proyectil : proyectilesEnemigos) {
                proyectil.draw(window);
            }
            for (auto &enemigo : enemigos) {
                enemigo.draw(window);
            }
            window.draw(scoreText); // Dibujar el tiempo jugado
            window.display();
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}