#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Pelota
{
private:
    float radio;
    float posx;
    float posy;
    b2Body *cuerpoBola;
    bool enContacto; // Variable para verificar si la pelota está tocando algo
    sf::Texture textura;

public:
    Pelota(b2World &mundo, float radio, float posx, float posy)
    {
        this->radio = radio;
        this->posx = posx;
        this->posy = posy;
        enContacto = false; // Inicialmente no está en contacto con nada



        if(!textura.loadFromFile("./assets/images/noFilter.png")){

            std::cout<<"Error";
        }

        // Crear cuerpo de la bola
        b2BodyDef cuerpoBolaDef;
        cuerpoBolaDef.type = b2_dynamicBody;
        cuerpoBolaDef.position.Set(this->posx, this->posy);
        this->cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

        // Crear la forma de la bola
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
    bola.setTexture(&textura);

    // Establecer la posición de la pelota en función del cuerpo físico
    bola.setPosition(
        cuerpoBola->GetPosition().x,
        cuerpoBola->GetPosition().y);

    // Ajustar la rotación de la figura para que coincida con la rotación del cuerpo físico
    float angulo = cuerpoBola->GetAngle();  // Obtener el ángulo de rotación en radianes
    bola.setRotation(angulo * 180 / 3.14159265359f);  // Convertir de radianes a grados

    return bola;
}

    b2Body* ObtenerCuerpo()
{
    return cuerpoBola;
}

    b2Vec2 ObtenerPosicion()
    {
        return cuerpoBola->GetPosition();
    }

    // Método para mover la pelota hacia la derecha
    void MoverDe(int fuerza)
    {
        cuerpoBola->ApplyForceToCenter(b2Vec2(-fuerza, 0.0f), true);
    }

    // Método para mover la pelota hacia la izquierda
    void MoverIzq(int fuerza)
    {
        cuerpoBola->ApplyForceToCenter(b2Vec2(fuerza, 0.0f), true);
    }

    // Método para detectar si la pelota está en contacto con algo
    void DetectarContacto()
    {
        enContacto = false; // Reseteamos el estado de contacto

        // Comprobamos todos los contactos del cuerpo (la pelota)
        for (b2ContactEdge* contacto = cuerpoBola->GetContactList(); contacto; contacto = contacto->next)
        {
            if (contacto->contact)
            {
                enContacto = true; // Si hay un contacto, la pelota está tocando algo
                break; // No necesitamos seguir verificando más contactos
            }
        }
    }

    // Método para hacer saltar la pelota solo si está en contacto con algo
    void Saltar(int salto)
    {
        DetectarContacto(); // Detectamos si está en contacto con algo
        if (enContacto)
        {
            cuerpoBola->ApplyForceToCenter(b2Vec2(0.0f, -salto), true); // Si está en contacto, la pelota salta
        }
    }
};