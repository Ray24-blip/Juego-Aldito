#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;

sf::RenderWindow ventana(sf::VideoMode(1366, 720), "Redball!");

int main()
{

    int fuerza = 1;

    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    b2BodyDef cuerpoSueloDef;
    cuerpoSueloDef.position.Set(200, 500.0f);
    b2Body *cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

    b2PolygonShape formaSuelo;
    int boxWidth = 600;
    int boxHeight = 10;
    formaSuelo.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);

    b2FixtureDef fixtureSueloDef;
    fixtureSueloDef.shape = &formaSuelo;
    fixtureSueloDef.friction = 1.0f;
    cuerpoSuelo->CreateFixture(&fixtureSueloDef);

    b2BodyDef cuerpoSueloDef2;
    cuerpoSueloDef2.position.Set(1000, 480.0f);
    b2Body *cuerpoSuelo2 = mundo.CreateBody(&cuerpoSueloDef2);

    b2PolygonShape formaSuelo2;
    int boxWidth2 = 600;
    int boxHeight2 = 10;
    formaSuelo2.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);

    b2FixtureDef fixtureSueloDef2;
    fixtureSueloDef2.shape = &formaSuelo2;
    fixtureSueloDef2.friction = 1.0f;
    cuerpoSuelo2->CreateFixture(&fixtureSueloDef2);

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
            cuerpoBola->ApplyForceToCenter(b2Vec2(0.0f, -50), true);

        mundo.Step(1.0f / 60.0f, 6, 2);
        cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;

        ventana.clear();

        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f);
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x,
            cuerpoSuelo->GetPosition().y);
        ventana.draw(suelo);

        sf::RectangleShape suelo2(sf::Vector2f(boxWidth, boxHeight));
        suelo2.setOrigin(boxWidth2 / 2.0f, boxHeight2 / 2.0f); // El origen x,y está en el centro de la forma
        suelo2.setPosition(
            cuerpoSuelo2->GetPosition().x,
            cuerpoSuelo2->GetPosition().y);
        ventana.draw(suelo2);

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