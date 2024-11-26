#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <Plataforma.hpp>
#include <Pelota.hpp>
using namespace std;

sf::RenderWindow ventana(sf::VideoMode(1366, 720), "Redball!");

int main()
{

    int fuerza = 2;

    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    Plataforma p1(mundo, 200, 500, 10, 600);
    Plataforma p2(mundo, 1000, 480, 10, 600);
    Plataforma p3(mundo, 1000, 200, 10, 300);

    Pelota pe1(mundo, 10, 400, 300);

    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            pe1.Mover(fuerza);


        // Calcular simulacion fisica
        mundo.Step(1.0f / 60.0f, 6, 2);
        // cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;

        ventana.clear();

        ventana.draw(p1.ObtenerFigura());
        ventana.draw(p2.ObtenerFigura());
        ventana.draw(p3.ObtenerFigura());

        ventana.draw(pe1.ObtenerFiguraPe());

        ventana.display();
    }

    return 0;
}