#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include "../include/ClasePersonaje.hpp"
#include "../include/ClaseProyectil.hpp"
#include "../include/ClaseEnemigo.hpp"
#include "../include/ClaseRecursos.hpp"
#include "../include/ClaseControl.hpp"

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

    try {
        Recursos recursos(window);
        Personaje dino("assets/images/Avion.png", sf::Vector2f(0, 50));
        Control control(dino, velocidad);

        // Pantalla de inicio
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                gameClock.restart();
                break;
            }

            window.clear();
            recursos.drawStartScreen();
            window.display();
        }

        sf::Clock enemySpawnClock;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            float deltaTime = clock.restart().asSeconds();
            int gameTime = static_cast<int>(gameClock.getElapsedTime().asSeconds());

            control.update(deltaTime, proyectiles, velocidadProyectil);

            for (auto &proyectil : proyectiles) {
                proyectil.move(deltaTime);
            }

            for (auto &proyectil : proyectilesEnemigos) {
                proyectil.move(deltaTime);
            }

            proyectiles.erase(std::remove_if(proyectiles.begin(), proyectiles.end(), [&window](const Proyectil &proyectil) {
                return proyectil.getPosition().x > window.getSize().x;
            }), proyectiles.end());

            proyectilesEnemigos.erase(std::remove_if(proyectilesEnemigos.begin(), proyectilesEnemigos.end(), [&window](const Proyectil &proyectil) {
                return proyectil.getPosition().y > window.getSize().y || proyectil.getPosition().y < 0;
            }), proyectilesEnemigos.end());

            if (enemySpawnClock.getElapsedTime().asSeconds() > 2.0f) {
                enemigos.push_back(Enemigo(sf::Vector2f(window.getSize().x, rand() % window.getSize().y), recursos.getEnemyTexture()));
                enemySpawnClock.restart();
            }

            for (auto &enemigo : enemigos) {
                enemigo.move(-velocidadEnemigo * deltaTime, 0);
                if (enemigo.canShoot()) {
                    proyectilesEnemigos.push_back(Proyectil(sf::Vector2f(enemigo.getPosition().x, enemigo.getPosition().y + 15), sf::Vector2f(-velocidadProyectil, 0)));
                }
            }

            enemigos.erase(std::remove_if(enemigos.begin(), enemigos.end(), [&window](const Enemigo &enemigo) {
                return enemigo.getPosition().x + enemigo.getBounds().width < 0;
            }), enemigos.end());

            for (auto &proyectil : proyectilesEnemigos) {
                if (proyectil.getBounds().intersects(dino.getBounds())) {
                    window.clear();
                    recursos.drawGameBackground();
                    recursos.drawGameOver();
                    window.display();
                    sf::sleep(sf::seconds(3));
                    while (true) {
                        sf::Event event;
                        while (window.pollEvent(event)) {
                            if (event.type == sf::Event::Closed) {
                                window.close();
                                return 0;
                            }
                        }
                        window.clear();
                        recursos.drawStartScreen();
                        window.display();
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
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

            for (auto enemigoIt = enemigos.begin(); enemigoIt != enemigos.end();) {
                bool enemigoImpactado = false;
                for (auto proyectilIt = proyectiles.begin(); proyectilIt != proyectiles.end();) {
                    if (proyectilIt->getBounds().intersects(enemigoIt->getBounds())) {
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

            window.clear();
            recursos.drawGameBackground();
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
            recursos.drawScore(gameTime);
            window.display();
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
