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
    float posx;
    float posy;
    b2Body *cuerpoSuelo;
    sf::Texture textura;

public:
    // Constructor
    PlataformaLetal(b2World &mundo, float posx, float posy, float alto, float ancho, const std::string &rutaTextura)
    {
        this->alto = alto;
        this->ancho = ancho;
        this->posx = posx;
        this->posy = posy;

        if (!textura.loadFromFile(rutaTextura))
        {

            std::cout << "Error";
        }

        b2BodyDef cuerpoSueloDef;
        cuerpoSueloDef.position.Set(this->posx, this->posy);
        this->cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

        b2PolygonShape formaSuelo;
        formaSuelo.SetAsBox(this->ancho / 2.0f, this->alto / 2.0f);

        b2FixtureDef fixtureSueloDef;
        fixtureSueloDef.shape = &formaSuelo;
        fixtureSueloDef.friction = 1.0f;
        this->cuerpoSuelo->CreateFixture(&fixtureSueloDef);
    }

    // Destructor
    ~PlataformaLetal() {}

    // Método para obtener la representación gráfica de la plataforma
    sf::RectangleShape ObtenerFigura()
    {
        sf::RectangleShape suelo(sf::Vector2f(this->ancho, this->alto));
        suelo.setOrigin(this->ancho / 2.0f, this->alto / 2.0f);
        suelo.setTexture(&textura);
        // Color rojo para la plataforma letal
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x,
            cuerpoSuelo->GetPosition().y);
        return suelo;
    }

    // Método para verificar si la pelota está tocando la plataforma letal
    bool VerificarColision(b2Body *cuerpoBola)
    {
        for (b2ContactEdge *contacto = cuerpoBola->GetContactList(); contacto; contacto = contacto->next)
        {
            if (contacto->contact)
            {
                // Verificar si el cuerpo de la pelota está tocando la plataforma letal
                b2Fixture *fixture = contacto->contact->GetFixtureA();
                if (fixture->GetBody() == cuerpoSuelo)
                {
                    return true; // Si hay colisión, retornar true
                }
            }
        }
        return false; // Si no hay colisión, retornar false
    }
};

#endif // PLATAFORMALETAL_HPP