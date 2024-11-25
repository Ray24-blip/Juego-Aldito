#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Plataforma
{
private:
    float alto;
    float ancho;
    float posx;
    float posy;
    b2Body *cuerpoSuelo;
    

public:
    Plataforma(b2World &mundo, float posx, float posy, float alto, float ancho)
    {
        this->alto = alto;
        this->ancho = ancho;
        this->posx = posx;
        this->posy = posy;

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
    ~Plataforma() {}

    sf::RectangleShape ObtenerFigura()
    {
        sf::RectangleShape suelo(sf::Vector2f(this->ancho, this->alto));
        suelo.setOrigin(this->ancho / 2.0f, this->alto / 2.0f);
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x,
            cuerpoSuelo->GetPosition().y);
        return suelo;
    }
};