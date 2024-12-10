#ifndef SONIDOSALTO_HPP
#define SONIDOSALTO_HPP

#include <SFML/Audio.hpp>
#include <string>

class SonidoSalto
{
public:

    SonidoSalto(const std::string& archivo)
    {
        if (!bufferSalto.loadFromFile(archivo)) {
            std::cerr << "Error al cargar el archivo de sonido de salto." << std::endl;
            throw std::runtime_error("No se pudo cargar el sonido de salto");
        }
        sonidoSalto.setBuffer(bufferSalto);
    }


    void reproducir()
    {
        sonidoSalto.play();
    }

private:
    sf::SoundBuffer bufferSalto;
    sf::Sound sonidoSalto;
};

#endif 