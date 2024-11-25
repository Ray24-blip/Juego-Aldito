#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <Plataforma.hpp>
using namespace std;

sf::RenderWindow ventana(sf::VideoMode(1366, 720), "Redball!");

int main()
{

    int fuerza = 2;

    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    Plataforma p1(mundo,200,500,10,600);
    Plataforma p2(mundo,1000,480,10,600);
    Plataforma p3(mundo,1000,200,10,300);

    b2BodyDef cuerpoBolaDef;
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position.Set(400.0f, 300.0f);
    b2Body *cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    b2CircleShape formaBola;
    formaBola.m_radius = 10.0f;

    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.7f;
    cuerpoBola->CreateFixture(&fixtureBolaDef);

    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cuerpoBola->ApplyForceToCenter(b2Vec2(-fuerza, 0.0f), true);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cuerpoBola->ApplyForceToCenter(b2Vec2(fuerza, 0.0f), true);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            cuerpoBola->ApplyForceToCenter(b2Vec2(0.0f, -35), true);

        // Calcular simulacion fisica
        mundo.Step(1.0f / 60.0f, 6, 2);
        // cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;

        ventana.clear();

       
        ventana.draw(p1.ObtenerFigura());
        ventana.draw(p2.ObtenerFigura());
        ventana.draw(p3.ObtenerFigura());

        sf::CircleShape bola(formaBola.m_radius);
        bola.setOrigin(formaBola.m_radius, formaBola.m_radius);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(
            cuerpoBola->GetPosition().x,
            cuerpoBola->GetPosition().y);
        ventana.draw(bola);

        ventana.display();
    }

    return 0;
}