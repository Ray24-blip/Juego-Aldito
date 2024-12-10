#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Pelota
{
private:
    float radio;
    float posX;
    float posY;
    b2Body *cuerpoBola;
    bool enContacto; 
    sf::Texture textura;

public:
    Pelota(b2World &mundo, float radio, float posX, float posY)
    {
        this->radio = radio;
        this->posX = posX;
        this->posY = posY;
        enContacto = false; 

        if (!textura.loadFromFile("./assets/images/noFilter.png"))
        {

            std::cout << "Error";
        }


        b2BodyDef cuerpoBolaDef;
        cuerpoBolaDef.type = b2_dynamicBody;
        cuerpoBolaDef.position.Set(this->posX, this->posY);
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

    sf::CircleShape obtenerFiguraPe()
    {
        sf::CircleShape bola(this->radio);
        bola.setOrigin(this->radio, this->radio);
        bola.setFillColor(sf::Color::Red);
        bola.setTexture(&textura);


        bola.setPosition(
            cuerpoBola->GetPosition().x,
            cuerpoBola->GetPosition().y);

     
        float angulo = cuerpoBola->GetAngle(); 
        bola.setRotation(angulo * 180 / 3.14159265359f); 

        return bola;
    }

    b2Body *obtenerCuerpo()
    {
        return cuerpoBola;
    }

    b2Vec2 obtenerPosicion()
    {
        return cuerpoBola->GetPosition();
    }


    void moverDe(int fuerza)
    {
        cuerpoBola->ApplyForceToCenter(b2Vec2(-fuerza, 0.0f), true);
    }


    void moverIzq(int fuerza)
    {
        cuerpoBola->ApplyForceToCenter(b2Vec2(fuerza, 0.0f), true);
    }


    void detectarContacto()
    {
        enContacto = false; 


        for (b2ContactEdge *contacto = cuerpoBola->GetContactList(); contacto; contacto = contacto->next)
        {
            if (contacto->contact)
            {
                enContacto = true; 
                break;             
            }
        }
    }


    void saltar(int salto)
    {
        detectarContacto(); go
        if (enContacto)
        {
            cuerpoBola->ApplyForceToCenter(b2Vec2(0.0f, -salto), true); 
        }
    }
};