#include <SFML/Audio.hpp>
#include <iostream>

class Musica {
private:
    sf::Music musica;

public:
    // Constructor que carga la música
    Musica(const std::string& rutaArchivo) {
        if (!musica.openFromFile(rutaArchivo)) {
            throw std::runtime_error("Error: No se pudo cargar la música de fondo.");
        }
    }

    // Iniciar la reproducción de la música
    void reproducir(float volumen = 50.0f, bool enBucle = true) {
        musica.setVolume(volumen);  // Establecer el volumen (0-100)
        musica.setLoop(enBucle);    // Establecer si debe repetirse en bucle
        musica.play();              // Iniciar la reproducción
    }

    // Detener la música
    void detener() {
        musica.stop();
    }
};