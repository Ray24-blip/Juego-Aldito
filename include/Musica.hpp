#include <SFML/Audio.hpp>
#include <iostream>

class Musica
{
private:
    sf::Music musica;

public:
    Musica(const std::string &rutaArchivo)
    {
        if (!musica.openFromFile(rutaArchivo))
        {
            throw std::runtime_error("Error: No se pudo cargar la música de fondo.");
        }
    }

    void reproducir(float volumen = 50.0f, bool enBucle = true)
    {
        musica.setVolume(volumen);
        musica.setLoop(enBucle);
        musica.play();
    }

    void detener()
    {
        musica.stop();
    }
};