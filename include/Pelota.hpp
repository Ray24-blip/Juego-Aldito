#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Pelota
{
private:
    float radio;
    float posx;
    float posy;
    b2Body *cuerpoBola;

public:
    Pelota(b2World &mundo, float radio, float posx, float posy)
    {
        this->radio = radio;
        this->posx = posx;
        this->posy = posy;

        b2BodyDef cuerpoBolaDef;
        cuerpoBolaDef.type = b2_dynamicBody;
        cuerpoBolaDef.position.Set(this->posx, this->posy);
        this->cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

        b2CircleShape formaBola;
        formaBola.m_radius = radio;

        b2FixtureDef fixtureBolaDef;
        fixtureBolaDef.shape = &formaBola;
        fixtureBolaDef.density = 0.01f;
        fixtureBolaDef.friction = 0.7f;
        cuerpoBola->CreateFixture(&fixtureBolaDef);
    }
    ~Pelota() {}

    sf::CircleShape ObtenerFiguraPe()
    {
        sf::CircleShape bola(this->radio);
        bola.setOrigin(this->radio, this->radio);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(
            cuerpoBola->GetPosition().x,
            cuerpoBola->GetPosition().y);
        return bola;
    }

    void Mover(int fuerza){

        cuerpoBola->ApplyForceToCenter(b2Vec2(-fuerza, 0.0f), true);

    }
};