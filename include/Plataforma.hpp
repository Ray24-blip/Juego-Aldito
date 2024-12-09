#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Plataforma
{
private:
    float alto;
    float ancho;
    float posX;
    float posY;
    b2Body *cuerpoSuelo;
    sf::Texture textura;

public:
    Plataforma(b2World &mundo, float posX, float posY, float alto, float ancho, const std::string &rutaTextura)
    {
        this->alto = alto;
        this->ancho = ancho;
        this->posX = posX;
        this->posY = posY;

        if(!textura.loadFromFile(rutaTextura)){

            std::cout<<"Error";
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
    ~Plataforma() {}

    sf::RectangleShape obtenerFigura()
    {
        sf::RectangleShape suelo(sf::Vector2f(this->ancho, this->alto));
        suelo.setOrigin(this->ancho / 2.0f, this->alto / 2.0f);
        suelo.setTexture(&textura);
        suelo.setFillColor(sf::Color::Green);
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x,
            cuerpoSuelo->GetPosition().y);
        return suelo;
    }
};