#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <Plataforma.hpp>
#include <Pelota.hpp>
#include <Colision.hpp>
#include <PlataformaLetal.hpp>
#include <Fondo.hpp>
#include <Musica.hpp>
#include <SonidoSalto.hpp>
#include <Cronometro.hpp>

using namespace std;

sf::RenderWindow ventana(sf::VideoMode(1366, 720), "Redball!");

int main()
{
    try
    {
        // Crear música de fondo
        Musica musica("./assets/music/music.ogg"); // Cambia "musica.ogg" por tu archivo de audio
        musica.reproducir(20.0f, true);            // Reproducir con volumen al 20% y en bucle

        // Crear objeto SonidoSalto
        SonidoSalto sonidoSalto("./assets/sounds/slime_jump.wav"); // Cargar sonido de salto

        int fuerza = 1;
        int salto = 500;
        b2Vec2 vectorGravedad(0.0f, 1.0f);
        b2World mundo(vectorGravedad);

        // Crear fondo (ajusta el tamaño del mundo según tu diseño)
        const int anchoMundo = 5000;
        const int altoMundo = 5000;
        Fondo fondo("./assets/images/FondoCielo.png", anchoMundo, altoMundo);

        sf::View vista(ventana.getDefaultView());

        Cronometro cronometro(30, "./assets/fonts/DS-DIGI.ttf");
        Plataforma p1(mundo, 220, 500, 10, 400, "./assets/images/grass_0.png");
        Plataforma p2(mundo, 1000, 480, 10, 600, "./assets/images/grass_0.png");
        Plataforma p3(mundo, 1550, 400, 10, 200, "./assets/images/grass_0.png");
        Plataforma p4(mundo, 2000, 400, 10, 200, "./assets/images/grass_0.png");
        Plataforma p5(mundo, 2450, 400, 10, 200, "./assets/images/grass_0.png");
        Plataforma p6(mundo, 3100, 400, 10, 500, "./assets/images/grass_0.png");
        // Plataforma p7(mundo, 1000, 350, 10, 300,"./assets/images/grass_0.png");

        PlataformaLetal pl1(mundo, 2700, 320, 80, 10, "./assets/images/Lava #4.png");
        PlataformaLetal pl2(mundo, 2700, 170, 80, 10, "./assets/images/Lava #4.png");

        Pelota pe1(mundo, 10, 200, 300);

        while (ventana.isOpen())
        {
            sf::Event evento;
            while (ventana.pollEvent(evento))
            {
                if (evento.type == sf::Event::Closed)
                    ventana.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                pe1.moverDe(fuerza);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                pe1.moverIzq(fuerza);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                pe1.saltar(salto);
                sonidoSalto.reproducir(); // Reproducir el sonido de salto
            }

            // Calcular simulación física
            mundo.Step(1.0f / 60.0f, 6, 2);
            cout << "Posición de la bola: " << pe1.obtenerPosicion().x << ", " << pe1.obtenerPosicion().y << endl;

            b2Vec2 posicionPelota = pe1.obtenerPosicion();
            if (pl1.VerificarColision(pe1.obtenerCuerpo()) || pl2.VerificarColision(pe1.obtenerCuerpo()) || posicionPelota.y > 800)
            {
                pe1.resetPosition();
            }

            if (posicionPelota.x >= 3000.0f)
            {
                cronometro.pausar();
                float tiempoFinal = cronometro.obtenerTiempoFinal();
                ventana.close();
                std::cout << "Juego terminado. Tiempo final: " << tiempoFinal << " segundos." << std::endl;
            }

            vista.setCenter(posicionPelota.x, posicionPelota.y);
            ventana.setView(vista);
            cronometro.actualizar();

            ventana.clear();

            // Dibujar el fondo
            fondo.actualizar(vista, ventana);
            fondo.dibujar(ventana);
            cronometro.ajustarPosicion(vista);

            // Dibujar los objetos del juego
            ventana.draw(p1.obtenerFigura(sf::Color::Green));
            ventana.draw(p2.obtenerFigura(sf::Color::Green));
            ventana.draw(p3.obtenerFigura(sf::Color::Green));
            ventana.draw(p4.obtenerFigura(sf::Color::Green));
            ventana.draw(p5.obtenerFigura(sf::Color::Green));
            ventana.draw(p6.obtenerFigura(sf::Color::Green));
            ventana.draw(pl1.obtenerFigura());
            ventana.draw(pl2.obtenerFigura());
            ventana.draw(pe1.obtenerFiguraPe());
            cronometro.dibujar(ventana);
            ventana.display();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}