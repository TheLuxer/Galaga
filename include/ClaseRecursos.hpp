#ifndef CLASE_RECURSOS_HPP
#define CLASE_RECURSOS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdexcept>

class Recursos {
public:
    Recursos(sf::RenderWindow &window) : window(window) {
        // Cargar la imagen de fondo de la pantalla de inicio
        if (!startBackgroundTexture.loadFromFile("assets/images/Arcade.png")) {
            throw std::runtime_error("No se pudo cargar la imagen de fondo de la pantalla de inicio");
        }
        startBackgroundSprite.setTexture(startBackgroundTexture);
        startBackgroundSprite.setScale(
            (window.getSize().x / startBackgroundSprite.getLocalBounds().width) * 0.7f,
            window.getSize().y / startBackgroundSprite.getLocalBounds().height);
        startBackgroundSprite.setPosition(
            (window.getSize().x - startBackgroundSprite.getGlobalBounds().width) / 2, 0);

        // Cargar la imagen de fondo del juego
        if (!gameBackgroundTexture.loadFromFile("assets/images/Fondo.png")) {
            throw std::runtime_error("No se pudo cargar la imagen de fondo del juego");
        }
        gameBackgroundSprite.setTexture(gameBackgroundTexture);
        gameBackgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / gameBackgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / gameBackgroundTexture.getSize().y);

        // Cargar la textura del enemigo
        if (!enemyTexture.loadFromFile("assets/images/Ovi.png")) {
            throw std::runtime_error("No se pudo cargar la textura del enemigo");
        }

        // Cargar la fuente de texto
        if (!font.loadFromFile("assets/fonts/retro.ttf")) {
            throw std::runtime_error("No se pudo cargar la fuente retro.ttf");
        }

        // Configurar el texto del título
        title.setFont(font);
        title.setString("Bienvenido a Sky Rider");
        title.setCharacterSize(150);
        title.setFillColor(sf::Color::White);
        title.setPosition(
            (window.getSize().x - title.getGlobalBounds().width) / 2, 300);

        // Configurar las instrucciones
        instructions.setFont(font);
        instructions.setString("Presiona ENTER para comenzar");
        instructions.setCharacterSize(75);
        instructions.setFillColor(sf::Color::Yellow);
        instructions.setPosition(
            (window.getSize().x - instructions.getGlobalBounds().width) / 2, 450);

        // Configurar el texto del score
        scoreText.setFont(font);
        scoreText.setCharacterSize(50);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);

        // Configurar el texto de game over
        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(100);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(
            (window.getSize().x - gameOverText.getGlobalBounds().width) / 2,
            (window.getSize().y - gameOverText.getGlobalBounds().height) / 2);

        // Cargar y configurar la música
        if (!music.openFromFile("assets/music/Cyberpunk-Moonlight-Sonata.ogg")) {
            throw std::runtime_error("No se pudo cargar la música");
        }
        music.setLoop(true);
        music.play();
    }

    void drawStartScreen() {
        window.draw(startBackgroundSprite);
        window.draw(title);
        window.draw(instructions);
    }

    void drawGameBackground() {
        window.draw(gameBackgroundSprite);
    }

    void drawScore(int score) {
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
    }

    void drawGameOver() {
        window.draw(gameOverText);
    }

    sf::Texture &getEnemyTexture() {
        return enemyTexture;
    }

private:
    sf::RenderWindow &window;
    sf::Texture startBackgroundTexture, gameBackgroundTexture, enemyTexture;
    sf::Sprite startBackgroundSprite, gameBackgroundSprite;
    sf::Font font;
    sf::Text title, instructions, scoreText, gameOverText;
    sf::Music music; // Nueva propiedad para la música
};

#endif
