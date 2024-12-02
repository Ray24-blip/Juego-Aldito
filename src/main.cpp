#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <Plataforma.hpp>
#include <Caja.hpp>
#include <Colision.hpp>

using namespace std;

sf::RenderWindow ventana(sf::VideoMode(1366, 720), "Redball!");

int main()
{

    int fuerza = 1;
    int salto = 300;
    b2Vec2 vectorGravedad(0.0f, 1.0f);
    b2World mundo(vectorGravedad);

    MyContactListener contactListener;
    mundo.SetContactListener(&contactListener);
    sf::View vista(ventana.getDefaultView());

    Plataforma p1(mundo, 200, 500, 10, 600);
    Plataforma p2(mundo, 1000, 480, 10, 600);
    Plataforma p3(mundo, 1000, 200, 10, 300);

    Caja ca1(mundo, 20, 30);


    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ca1.MoverDe(fuerza);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ca1.MoverIzq(fuerza);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && contactListener.isGrounded)
        {
            ca1.Saltar(salto); 
        }


        // Calcular simulacion fisica
        mundo.Step(1.0f / 60.0f, 6, 2);
        // cout << "Posicion de la bola: " << pe1.getPosition().x << ", " << pe1.getPosition().y << endl;
        // cout << "Posicion del sensor: " << se1.getPosition().x << ", " << se1.getPosition().y << endl;

        b2Vec2 posicionCaja = ca1.ObtenerPosicion();
        vista.setCenter(posicionCaja.x, posicionCaja.y);
        ventana.setView(vista);

        ventana.clear();

        ventana.draw(p1.ObtenerFigura());
        ventana.draw(p2.ObtenerFigura());
        ventana.draw(p3.ObtenerFigura());

        ventana.draw(ca1.ObtenerFiguraPe());

        ventana.display();
    }

    return 0;
}