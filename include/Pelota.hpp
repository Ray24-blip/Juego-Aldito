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
        cuerpoBolaDef.fixedRotation = true;
        cuerpoBolaDef.type = b2_dynamicBody;
        cuerpoBolaDef.position.Set(this->posx, this->posy);
        this->cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

        // Fixture principal de la bola
        b2CircleShape formaBola;
        formaBola.m_radius = radio;

        b2FixtureDef fixtureBolaDef;
        fixtureBolaDef.shape = &formaBola;
        fixtureBolaDef.density = 0.01f;
        fixtureBolaDef.friction = 0.1f;
        this->cuerpoBola->CreateFixture(&fixtureBolaDef); // Crear el fixture principal

        // Crear un sensor como fixture adicional
        b2CircleShape sensorShape;
        sensorShape.m_radius = radio * 0.8f; // Radio del sensor (ligeramente menor que el de la bola)
        sensorShape.m_p.Set(0.0f, radio);    // Desplazar el sensor hacia abajo

        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true;                   // Marcar este fixture como sensor
        this->cuerpoBola->CreateFixture(&sensorFixtureDef); // Crear el fixture del sensor
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

    b2Vec2 velocidad1(){
        b2Vec2 velocidad = cuerpoBola->GetLinearVelocity();
        cuerpoBola->SetLinearVelocity(velocidad);
        return velocidad;
    }


    void MoverDe(int fuerza)
    {
        cuerpoBola->ApplyForceToCenter(b2Vec2(-fuerza, 0.0f), true);
    }

        void MoverIzq(int fuerza)
    {
        cuerpoBola->ApplyForceToCenter(b2Vec2(fuerza, 0.0f), true);
    }

    void Saltar(int salto)
    {

        cuerpoBola->ApplyForceToCenter(b2Vec2(0.0f, -salto), true);
    }
    
};