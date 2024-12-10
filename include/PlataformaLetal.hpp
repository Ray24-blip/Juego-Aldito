#ifndef PLATAFORMALETAL_HPP
#define PLATAFORMALETAL_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class PlataformaLetal
{
private:
    float alto;
    float ancho;
    float posX;
    float posY;
    b2Body *cuerpoSuelo;
    sf::Texture textura;

public:
    PlataformaLetal(b2World &mundo, float posX, float posY, float alto, float ancho, const std::string &rutaTextura)
    {
        this->alto = alto;
        this->ancho = ancho;
        this->posX = posX;
        this->posY = posY;

        if (!textura.loadFromFile(rutaTextura))
        {

            std::cout << "Error";
        }

        b2BodyDef cuerpoSueloDef;
        cuerpoSueloDef.position.Set(this->posX, this->posY);
        this->cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

        b2PolygonShape formaSuelo;
        formaSuelo.SetAsBox(this->ancho / 2.0f, this->alto / 2.0f);

        b2FixtureDef fixtureSueloDef;
        fixtureSueloDef.shape = &formaSuelo;
        fixtureSueloDef.friction = 1.0f;
        this->cuerpoSuelo->CreateFixture(&fixtureSueloDef);
    }

    ~PlataformaLetal() {}

    sf::RectangleShape obtenerFigura()
    {
        sf::RectangleShape suelo(sf::Vector2f(this->ancho, this->alto));
        suelo.setOrigin(this->ancho / 2.0f, this->alto / 2.0f);
        suelo.setTexture(&textura);
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x,
            cuerpoSuelo->GetPosition().y);
        return suelo;
    }

    bool VerificarColision(b2Body *cuerpoBola)
    {
        for (b2ContactEdge *contacto = cuerpoBola->GetContactList(); contacto; contacto = contacto->next)
        {
            if (contacto->contact)
            {
                b2Fixture *fixture = contacto->contact->GetFixtureA();
                if (fixture->GetBody() == cuerpoSuelo)
                {
                    return true;
                }
            }
        }
        return false;
    }
};

#endif 