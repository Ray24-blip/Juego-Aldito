#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Caja
{
private:
    float radio;
    float posx;
    float posy;
    b2Body *cuerpoCaja;

public:
    Caja(b2World &mundo, float posx, float posy)
    {
        this->radio = radio;
        this->posx = posx;
        this->posy = posy;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(posx, posy);
        cuerpoCaja = mundo.CreateBody(&bodyDef);

        // Crear la caja para el personaje
        b2PolygonShape boxShape;
        boxShape.SetAsBox(0.5f, 1.0f); // El personaje tendrá un tamaño de 1x2

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &boxShape;
        fixtureDef.density = 0.3f;
        fixtureDef.friction = 0.4f;
        cuerpoCaja->CreateFixture(&fixtureDef);

        // Crear el fixture sensor para los pies
        b2PolygonShape sensorShape;
        sensorShape.SetAsBox(0.6f, 0.1f, b2Vec2(0.0f, -1.0f), 0.0f); // Sensor de 1x0.2 en los pies

        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true; // Esto lo convierte en un sensor
        cuerpoCaja->CreateFixture(&sensorFixtureDef);
    }

    ~Caja() {}

    sf::RectangleShape ObtenerFiguraPe()
    {
        sf::RectangleShape caja(sf::Vector2f(this->posx, this->posy));
        caja.setOrigin(this->posx/2, this->posy);
        caja.setPosition(
            cuerpoCaja->GetPosition().x,
            cuerpoCaja->GetPosition().y);
        return caja;
    }
    

      b2Vec2 ObtenerPosicion()
    {
        return cuerpoCaja->GetPosition();
    }

    void MoverDe(int fuerza)
    {
        cuerpoCaja->ApplyForceToCenter(b2Vec2(-fuerza, 0.0f), true);
    }

    void MoverIzq(int fuerza)
    {
        cuerpoCaja->ApplyForceToCenter(b2Vec2(fuerza, 0.0f), true);
    }

    void Saltar(int salto)
    {

        cuerpoCaja->ApplyForceToCenter(b2Vec2(0.0f, -salto), true);
    }
};