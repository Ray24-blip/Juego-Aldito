#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <Plataforma.hpp>
#include <Pelota.hpp>
#include <Colision.hpp>
#include <PlataformaLetal.hpp>

using namespace std;

sf::RenderWindow ventana(sf::VideoMode(1366, 720), "Redball!");

int main()
{

    int fuerza = 1;
    int salto = 500;
    b2Vec2 vectorGravedad(0.0f, 1.0f);
    b2World mundo(vectorGravedad);


    sf::View vista(ventana.getDefaultView());

    Plataforma p1(mundo, 200, 500, 10, 600);
    Plataforma p2(mundo, 1000, 480, 10, 600);
    Plataforma p3(mundo, 1000, 350, 10, 300);
    PlataformaLetal p4(mundo, 800,400,10,60);

    Pelota pe1(mundo,10, 200, 300);


    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            pe1.MoverDe(fuerza);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            pe1.MoverIzq(fuerza);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            pe1.Saltar(salto); 
        }

        
        // Calcular simulacion fisica
        mundo.Step(1.0f / 60.0f, 6, 2);
        cout << "Posicion de la bola: " << pe1.ObtenerPosicion().x << ", " << pe1.ObtenerPosicion().y << endl;
   

        b2Vec2 posicionPelota = pe1.ObtenerPosicion();
                if (p4.VerificarColision(pe1.ObtenerCuerpo()))
        {
            std::cout << "¡La pelota ha tocado la plataforma letal! El juego termina." << std::endl;
            ventana.close(); // Terminar el juego
        }
        if(posicionPelota.y>800){

            ventana.close();
        }

        vista.setCenter(posicionPelota.x, posicionPelota.y);
        ventana.setView(vista);

        ventana.clear();

        ventana.draw(p1.ObtenerFigura());
        ventana.draw(p2.ObtenerFigura());
        ventana.draw(p3.ObtenerFigura());
        ventana.draw(p4.ObtenerFigura());

        ventana.draw(pe1.ObtenerFiguraPe());

        ventana.display();
    }

    return 0;
}